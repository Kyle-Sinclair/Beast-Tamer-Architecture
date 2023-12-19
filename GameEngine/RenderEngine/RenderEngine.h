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

    inline static int width, height;
    inline static GPU_Rect* screenRect;

    inline static GPU_Target* screen;
    inline static GPU_Target* backScreen;

    inline static Shader* errorShader;
    inline static Shader* backgroundShader;
    inline static Shader* spriteShader;
    inline static Shader* userInterfaceShader;
    inline static Shader* postProcessShader;
    
    inline static GPU_Image* backImage;
    inline static GPU_Image* debugImage;
    
   // inline static GPU_Image* BackgroundImage;
    inline static ImageQuad backgroundQuad;
    //inline static GPU_Rect* sourceRect;
    //inline static GPU_Rect* destRect;
    

private:
    static void BlitScreen(GPU_Image* image, GPU_Target* target);
    static void RenderSprites();
    inline static std::list<ImageQuad> mElementsToRender;
};
