#pragma once
#include <SDL_render.h>
#include <set>

#include "TextureLoader.h"
#include "VisualElement.h"

class VisualElementFactory
{
    public:
    VisualElementFactory(SDL_Renderer* renderer);
    TextureLoader* textureLoader;
    SDL_Renderer* renderer;
    VisualElement* CreateVisualElement(const char* path, int x = 0,int y = 0,int w= 1,int h= 1,int spriteIndex = 0,int columns = 0, int rows = 0);
    std::set<VisualElement*> VisualElementSet;
};
