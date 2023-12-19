#pragma once
#include <SDL_render.h>
#include <set>
#include <unordered_map>

#include "TextureLoader.h"
#include "VisualElement.h"

class VisualElementFactory
{
    public:
    VisualElementFactory();
    TextureLoader* textureLoader;
    VisualElement* CreateVisualElement(const char* path,
        RectTransform rectTransform = RectTransform(),
        int spriteIndex = 0,int columns = 0, int rows = 0);
    std::set<VisualElement*> visualElementSet;
};
