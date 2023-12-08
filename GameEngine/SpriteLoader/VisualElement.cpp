#include "VisualElement.h"

#include <algorithm>


VisualElement::VisualElement(SDL_Renderer* renderer,Texture* texture, int w, int h, int x, int y)
{
    this->renderer = renderer;
    this->texture = texture;
    isClipped = false;
    rect = {x,y,texture->GetWidth(),texture->GetHeight()};
    RectTransform.Size.x = w;
    RectTransform.Size.y = h;
    RectTransform.Position.x = x;
    RectTransform.Position.y = y;
}

VisualElement::VisualElement(Texture* texture,SDL_Renderer* renderer, int spriteIndex, int columns, int rows, int w, int h, int x, int y)
{
    this->renderer = renderer;
    this->texture = texture;
    rect = {x,y,w,h};
    
    isClipped = true;
    spriteSheetLength = (columns * rows);
    spriteIndex = std::clamp(spriteIndex,0,spriteSheetLength);
    this->spriteIndex = spriteIndex;

    
    int clippedWidth = texture->GetWidth() / columns;
    int clippedHeight = texture->GetHeight() / rows;
    
    int clippedX = (spriteIndex % columns) * clippedWidth;
   // int clippedY = (spriteIndex / rows) * clippedHeight;
    
    int clippedY = ((spriteIndex - (spriteIndex % columns))/columns) * clippedHeight;
    clippedRect = {clippedX,clippedY,clippedWidth,clippedHeight};
    rect.h = clippedHeight;
    rect.w = clippedWidth;

    RectTransform.Size.x = w;
    RectTransform.Size.y = h;
    RectTransform.Position.x = x;
    RectTransform.Position.y = y;
}

void VisualElement::Render()
{
    SDL_Rect transformedRect
    {
        (int)RectTransform.Position.x,
        (int)RectTransform.Position.y,
        (int)RectTransform.Size.x * rect.w,
        (int)RectTransform.Size.y * rect.h
    };
    
    SDL_RenderCopy(renderer,texture->GetTexture(),(isClipped)? &clippedRect: NULL, &transformedRect);
}
