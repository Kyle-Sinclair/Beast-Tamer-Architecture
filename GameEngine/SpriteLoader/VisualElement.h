#pragma once

#include <SDL_render.h>

#include "RectTransform.h"
#include "TextureLoader.h"

class VisualElement
{
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Rect clippedRect;
    RectTransform RectTransform;
    
    bool isClipped;
    int spriteIndex;
    int spriteSheetLength = 0;

    Texture* texture;
public:
    //Renderer and texture are switched to avoid ambigous function calls;
    VisualElement(SDL_Renderer* renderer,Texture* texture,int w = 1, int h = 1, int x = 0, int y = 0);
    VisualElement(Texture* texture, SDL_Renderer* renderer,int spriteIndex,int columns,int rows,int w = 1, int h = 1, int x = 0, int y = 0);

    void Render();
};
