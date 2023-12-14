#pragma once

#include <SDL_gpu.h>

#include "Shader.h"
#include "../SpriteLoader/VisualElement.h"

class RenderEngine
{
public:
    static bool Init();

    static void PreRenderCheck();
    static void Render();

    static void Quit();

    inline static int Width, Height;
    inline static GPU_Rect* ScreenRect;

    inline static GPU_Target* Screen;
    inline static GPU_Target* BackScreen;

    inline static Shader* ErrorShader;
    inline static Shader* BackgroundShader;
    inline static Shader* SpriteShader;
    inline static Shader* UserInterfaceShader;
    inline static Shader* PostProcessShader;
    
    inline static GPU_Image* BackImage;
    inline static GPU_Image* DebugImage;
    
    inline static GPU_Image* BackgroundImage;
    inline static GPU_Rect* sourceRect;
    inline static GPU_Rect* destRect;
    

private:
    static void BlitScreen(GPU_Image* image, GPU_Target* target);

    
};
