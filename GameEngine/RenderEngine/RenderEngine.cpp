#include "RenderEngine.h"

#include <algorithm>
#include <cstdio>
#include <SDL.h>

#include "Shader.h"
#include "../Global.h"
#include "../SubSystems/SubsystemCollection.h"
#include "../SubSystems/VisualElementSubSystem.h"

bool RenderEngine::Init()
{
    // Init main buffer
    Screen = GPU_Init(SCREEN_WIDTH, SCREEN_HEIGHT, GPU_DEFAULT_INIT_FLAGS | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    ScreenRect = new GPU_Rect();
    if (!Screen)
    {
        printf("SDL_GPU: Window could not be created!\n");
        return false;
    }
    gWindow = SDL_GetWindowFromID(Screen->context->windowID);
    //SDL_RenderSetLogicalSize(SDL_GetRenderer(gWindow), INTERNAL_SCREEN_WIDTH, INTERNAL_SCREEN_HEIGHT); TODO: Figure out why this doesn't work.
    SDL_SetWindowMinimumSize(gWindow, INTERNAL_SCREEN_WIDTH, INTERNAL_SCREEN_HEIGHT);
    
    // Init back buffer
    GPU_Image* backImage = GPU_CreateImage(INTERNAL_SCREEN_WIDTH, INTERNAL_SCREEN_HEIGHT, GPU_FORMAT_RGBA);
    BackScreen = GPU_LoadTarget(backImage);
    
    GPU_EnableCamera(Screen, true);

    ErrorShader = new Shader("Background", "Resources/Shaders/Error.vert", "Resources/Shaders/Error.frag");
    if (!ErrorShader->DidCompile())
    {
        return false;
    }
    
    BackgroundShader = new Shader("Background", "Resources/Shaders/Background.vert", "Resources/Shaders/Background.frag");
    SpriteShader = new Shader("Sprite", "Resources/Shaders/Sprite.vert", "Resources/Shaders/Sprite.frag");
    PostProcessShader = new Shader("PostProcessing", "Resources/Shaders/PostProcessing.vert", "Resources/Shaders/PostProcessing.frag");
    gSubsystemCollection->GetSubSystem<VisualElementSubSystem>();
   /* BackgroundImage = GPU_LoadImage("Resources/PokemonSprites/BackgroundTest.png");
    GPU_SetImageFilter(BackgroundImage, GPU_FILTER_NEAREST);
    if (BackgroundImage)
    {
        GPU_GenerateMipmaps(BackgroundImage);
    }*/
    
    DebugImage = GPU_LoadImage("Resources/PokemonSprites/Debug.png");
    if (DebugImage)
    {
        GPU_SetWrapMode(DebugImage, GPU_WRAP_MIRRORED, GPU_WRAP_MIRRORED);
        GPU_GenerateMipmaps(DebugImage);
    }

    gWindowDirty = true;

    return true;
}

void RenderEngine::PreRenderCheck()
{
    if(gSubsystemCollection->GetSubSystem<VisualElementSubSystem>()->HasBeenDirtied())
    {
        VisualElementSubSystem* subsystem = gSubsystemCollection->GetSubSystem<VisualElementSubSystem>();
        //printf(__FUNCTION__);
        
        VisualElement* visual_element =  subsystem->BackgoundVisualElement;
        BackgroundQuad = visual_element->GetImageQuad();
        ElementsToRender.clear();
        
        for(auto element : subsystem->CurrentNonBackgroundVisualElements)
        {
            ElementsToRender.push_back(element->GetImageQuad());
        }
    }
}


void RenderEngine::Render()
{
    const float InternalWidth = INTERNAL_SCREEN_WIDTH;
    const float InternalHeight = INTERNAL_SCREEN_HEIGHT;
    
    // Reference: https://github.com/grimfang4/sdl-gpu/blob/master/demos/simple-shader/main.c
    const float time = static_cast<float>(SDL_GetTicks()) * 0.001f;

    // Gets dirtied by input system for now
    if(gWindowDirty)
    {
        SDL_GetWindowSize(gWindow, &Width, &Height);
        GPU_SetWindowResolution(Width, Height);

        const float ratioX = Width / InternalWidth;
        const float ratioY = Height / InternalHeight;
        const float ratio = ratioX < ratioY ? ratioX : ratioY;

        const float newWidth = ratio * InternalWidth;
        const float newHeight = ratio * InternalHeight;

        const float padX = (Width - newWidth) * 0.5f;
        const float padY = (Height - newHeight) * 0.5f;
        
        ScreenRect->x = padX;
        ScreenRect->y = padY;
        ScreenRect->w = newWidth;
        ScreenRect->h = newHeight;
    }

    GPU_Clear(BackScreen);
    GPU_Clear(Screen);

    // Background
    if (BackgroundShader)
    {
        const auto shader = BackgroundShader->DidCompile() ? BackgroundShader : ErrorShader;
        auto backBlock = shader->GetBlock();
        GPU_ActivateShaderProgram(shader->GetProgram(), &backBlock);
        //GPU_ActivateShaderProgram(0, nullptr);
        shader->SetFloat("Time", time);
        shader->SetVec2("Resolution", InternalWidth, InternalHeight);
        shader->SetVec2("TexResolution", BackgroundQuad.Image->w, BackgroundQuad.Image->h);
        GPU_BlitRect(BackgroundQuad.Image,BackgroundQuad.SrcRect,BackScreen,BackgroundQuad.DstRect);
        //BlitScreen(BackgroundImage, BackScreen);
    }

    // Sprites
    if (SpriteShader)
    {
        const auto shader = SpriteShader->DidCompile() ? SpriteShader : ErrorShader;
        auto spriteBlock = shader->GetBlock();
        GPU_ActivateShaderProgram(shader->GetProgram(), &spriteBlock);
        shader->SetFloat("Time", time);
        shader->SetVec2("Resolution", InternalWidth, InternalHeight);
        GPU_Rect* spriteRect = new GPU_Rect(InternalWidth/2, InternalHeight/2, 64, 64);
        RenderSprites();
       // GPU_BlitRect(DebugImage, nullptr, BackScreen, spriteRect);
    }

    // UI
    if (UserInterfaceShader)
    {
        const auto shader = UserInterfaceShader->DidCompile() ? UserInterfaceShader : ErrorShader;
        auto uiBlock = shader->GetBlock();
        GPU_ActivateShaderProgram(shader->GetProgram(), &uiBlock);
        //BlitScreen(, BackScreen);
    }

    // Post processing: https://github.com/grimfang4/sdl-gpu/issues/240
    const bool postProcessingEnabled = true;
    if (PostProcessShader)
    {
        const auto shader = PostProcessShader->DidCompile() ? PostProcessShader : ErrorShader;
        auto postBlock = PostProcessShader->GetBlock();
        if (!postProcessingEnabled)
        {
            GPU_ActivateShaderProgram(0, nullptr);
        }
        else
        {
            GPU_ActivateShaderProgram(shader->GetProgram(), &postBlock);
            shader->SetFloat("Time", time);
            shader->SetVec2("Resolution", Width, Height);
            shader->SetVec2("TexResolution", InternalWidth, InternalHeight);
        }
        GPU_BlitRect(BackScreen->image, nullptr, Screen, ScreenRect);
    }
    
    GPU_Flip(Screen);
}

void RenderEngine::Quit()
{
    GPU_FreeTarget(Screen);
    GPU_FreeTarget(BackScreen);
    GPU_FreeShader(BackgroundShader->GetProgram());
    GPU_FreeShader(SpriteShader->GetProgram());
    GPU_FreeShader(UserInterfaceShader->GetProgram());
    GPU_FreeShader(PostProcessShader->GetProgram());
    GPU_FreeImage(DebugImage);
}

void RenderEngine::BlitScreen(GPU_Image* image, GPU_Target* target)
{
    GPU_BlitRect(image, nullptr, target, nullptr);
}

void RenderEngine::RenderSprites()
{
    for (auto quad : ElementsToRender)
    {
        GPU_BlitRect(quad.Image,quad.SrcRect,BackScreen,quad.DstRect);
    }
}


