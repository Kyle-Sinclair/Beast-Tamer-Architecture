#include "VisualElement.h"

#include <algorithm>


VisualElement::VisualElement(Texture* texture,RectTransform rectTransform)
{

    this->texture = texture;
    isClipped = false;
    rect = {rectTransform.Position.x,rectTransform.Position.y,texture->GetWidth_f(),texture->GetHeight_f()};
    this->rectTransform = rectTransform;
}

VisualElement::VisualElement(Texture* texture,int spriteIndex,int columns, int rows,RectTransform rectTransform)
{
    this->texture = texture;
    rect = {rectTransform.Position.x,rectTransform.Position.y,0,0};
    
    isClipped = true;
    spriteSheetLength = (columns * rows);
    spriteIndex = std::clamp(spriteIndex,0,spriteSheetLength);
    this->spriteIndex = spriteIndex;
    this->columns = columns;
    this->rows = rows;
    
    SetSpriteIndex(spriteIndex);
    const int clippedWidth = texture->GetImage()->w / columns;
    const int clippedHeight = texture->GetImage()->h / rows;
    rect.h = clippedRect.h = static_cast<float>(clippedWidth);
    rect.w = clippedRect.w = static_cast<float>(clippedHeight);

    this->rectTransform = rectTransform;
}

Vector VisualElement::GetOriginRenderPoint()
{
    Vector originDisplacement = GetOriginDisplacement();
    const int width = (isClipped)? clippedRect.w: rect.w;
    const int height = (isClipped)? clippedRect.h: rect.h;

    
    originDisplacement.x *= static_cast<float>(width) * rectTransform.Size.x;
    originDisplacement.y *= static_cast<float>(height) * rectTransform.Size.y;
    const Vector renderPoint = rectTransform.Position + originDisplacement;
    return renderPoint;
}

void VisualElement::SetSpriteIndex(int index)
{
    index = std::clamp(index,0,spriteSheetLength);
    const int clippedWidth = texture->GetImage()->w / columns;
    const int clippedHeight = texture->GetImage()->h / rows;
    
    const int clippedX = (index % columns) * clippedWidth;
    const int clippedY = ((index - (index % columns))/columns) * clippedHeight;

    clippedRect.x = static_cast<float>(clippedX);
    clippedRect.y = static_cast<float>(clippedY);
}

Vector VisualElement::GetOriginDisplacement()
{
    switch (rectTransform.originAnchorPoint)
    {
        case Center: return {-0.5,-0.5};
        case TopLeft: return {0,0};
        case TopRight: return{-1,0};
        case BottomLeft: return{0,-1};
        case BottomRight: return{-1,-1};
        case Top: return{-0.5,0};
        case Bottom: return{-0.5,-1};
        case Left: return{0,-0.5};
        case Right: return{-1,-0.5};
        default: return {0,0};
    }
}

/*void VisualElement::Render()
{
    Vector originRenderPoint = GetOriginRenderPoint();
    SDL_Rect transformedRect
    {
        (int)originRenderPoint.x,
        (int)originRenderPoint.y,
        (int)rectTransform.Size.x * rect.w,
        (int)rectTransform.Size.y * rect.h
    };
   // SDL_RenderCopy(renderer,texture->GetTexture(),(isClipped)? & clippedRect: NULL, &transformedRect);
}*/

bool VisualElement::IsClipped()
{
    return isClipped;
}

int VisualElement::GetSpriteIndex()
{
    return spriteIndex;
}

int VisualElement::GetColumns()
{
    return columns;
}

int VisualElement::GetRows()
{
    return rows;
}

int VisualElement::GetSpriteSheetLength()
{
    return spriteSheetLength;
}

GPU_Rect VisualElement::GetRenderRect()
{
    Vector originRenderPoint = GetOriginRenderPoint();
    
    GPU_Rect transformedRect
    {
        originRenderPoint.x,
        originRenderPoint.y,
        rectTransform.Size.x * rect.w,
        rectTransform.Size.y * rect.h
    };
    return transformedRect;
}

GPU_Rect VisualElement::GetSrcRect()
{
    return clippedRect;
}
