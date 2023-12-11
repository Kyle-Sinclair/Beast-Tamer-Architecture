#include "RenderEngine.h"

#include <cstdio>
#include <SDL.h>

#include "Shader.h"
#include "../Global.h"

bool RenderEngine::Init()
{
    // Init main buffer
    Screen = GPU_Init(SCREEN_WIDTH, SCREEN_HEIGHT, GPU_DEFAULT_INIT_FLAGS | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!Screen)
    {
        printf("SDL_GPU: Window could not be created!\n");
        return false;
    }
    gWindow = SDL_GetWindowFromID(Screen->context->windowID);
    
    // Init back buffer
    GPU_Image* backImage = GPU_CreateImage(SCREEN_WIDTH, SCREEN_HEIGHT, GPU_FORMAT_RGBA);
    BackScreen = GPU_LoadTarget(backImage);
    
    GPU_EnableCamera(Screen, true);

    ErrorShader = new Shader("Background", "Resources/Shaders/Error.vert", "Resources/Shaders/Error.frag");
    BackgroundShader = new Shader("Background", "Resources/Shaders/Background.vert", "Resources/Shaders/Background.frag");
    SpriteShader = new Shader("Sprite", "Resources/Shaders/Sprite.vert", "Resources/Shaders/Sprite.frag");
    PostProcessShader = new Shader("PostProcessing", "Resources/Shaders/PostProcessing.vert", "Resources/Shaders/PostProcessing.frag");

    BackgroundImage = GPU_LoadImage("Resources/PokemonSprites/Maps1.png");
    if (BackgroundImage)
    {
        GPU_GenerateMipmaps(BackgroundImage);
    }
    
    DebugImage = GPU_LoadImage("Resources/PokemonSprites/Debug.png");
    if (DebugImage)
    {
        GPU_SetWrapMode(DebugImage, GPU_WRAP_MIRRORED, GPU_WRAP_MIRRORED);
        GPU_GenerateMipmaps(DebugImage);
    }

    return true;
}

void RenderEngine::Render()
{
    // Reference: https://github.com/grimfang4/sdl-gpu/blob/master/demos/simple-shader/main.c
    const float time = static_cast<float>(SDL_GetTicks()) * 0.001f;

    // Temporary loop to get window resize event
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) gQuit = true;
        else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            SDL_GetWindowSize(gWindow, &Width, &Height);
            GPU_SetWindowResolution(Width, Height);

            // Allocate new back buffer
            GPU_FreeTarget(BackScreen);
            GPU_Image* backImage = GPU_CreateImage(Width, Height, GPU_FORMAT_RGBA);
            BackScreen = GPU_LoadTarget(backImage);
        }
    }

    GPU_Clear(Screen);

    // Background
    if (BackgroundShader)
    {
        const auto shader = BackgroundShader->DidCompile() ? BackgroundShader : ErrorShader;
        auto backBlock = shader->GetBlock();
        GPU_ActivateShaderProgram(shader->GetProgram(), &backBlock);
        //GPU_ActivateShaderProgram(0, nullptr);
        shader->SetFloat("Time", time);
        shader->SetVec2("Resolution", Width, Height);
        shader->SetVec2("TexResolution", BackgroundImage->w, BackgroundImage->h);
        GPU_BlitRect(BackgroundImage, nullptr, BackScreen, nullptr);
    }

    // Sprites
    if (SpriteShader)
    {
        const auto shader = SpriteShader->DidCompile() ? SpriteShader : ErrorShader;
        auto spriteBlock = shader->GetBlock();
        GPU_ActivateShaderProgram(shader->GetProgram(), &spriteBlock);
        shader->SetFloat("Time", time);
        shader->SetVec2("Resolution", Width, Height);
        GPU_Blit(DebugImage, nullptr, BackScreen, BackScreen->w/2, BackScreen->h/2);
    }

    // UI
    if (UserInterfaceShader)
    {
        const auto shader = UserInterfaceShader->DidCompile() ? UserInterfaceShader : ErrorShader;
        auto uiBlock = shader->GetBlock();
        GPU_ActivateShaderProgram(shader->GetProgram(), &uiBlock);
    }

    // Post processing: https://github.com/grimfang4/sdl-gpu/issues/240
    const bool postProcessingEnabled = false;
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
        }
        GPU_BlitRect(BackScreen->image, nullptr, Screen, nullptr);
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
