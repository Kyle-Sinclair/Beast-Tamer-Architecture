#include "VisualElement.h"

#include <algorithm>


VisualElement::VisualElement(Texture* texture,RectTransform rectTransform)
{

    this->mTexture = texture;
    mIsClipped = false;
    mRect = {rectTransform.Position.x,rectTransform.Position.y,texture->GetWidth_f(),texture->GetHeight_f()};
    this->mRectTransform = rectTransform;
}

VisualElement::VisualElement(Texture* texture,int spriteIndex,int columns, int rows,RectTransform rectTransform)
{
    this->mTexture = texture;
    mRect = {rectTransform.Position.x,rectTransform.Position.y,0,0};
    
    mIsClipped = true;
    mSpriteSheetLength = (columns * rows);
    spriteIndex = std::clamp(spriteIndex,0,mSpriteSheetLength);
    this->mSpriteIndex = spriteIndex;
    this->mColumns = columns;
    this->mRows = rows;
    
    SetSpriteIndex(spriteIndex);
    const int clippedWidth = texture->GetImage()->w / columns;
    const int clippedHeight = texture->GetImage()->h / rows;
    mRect.w = mClippedRect.w = static_cast<float>(clippedWidth);
    mRect.h = mClippedRect.h = static_cast<float>(clippedHeight);

    this->mRectTransform = rectTransform;
}

Vector VisualElement::GetOriginRenderPoint()
{
    Vector originDisplacement = GetOriginDisplacement();
    const int width = (mIsClipped)? mClippedRect.w: mRect.w;
    const int height = (mIsClipped)? mClippedRect.h: mRect.h;
    
    originDisplacement.x *= static_cast<float>(width) * mRectTransform.Size.x;
    originDisplacement.y *= static_cast<float>(height) * mRectTransform.Size.y;
    const Vector renderPoint = mRectTransform.Position + originDisplacement;
    return renderPoint;
}

void VisualElement::SetSpriteIndex(int index)
{
    index = std::clamp(index,0,mSpriteSheetLength);
    const int clippedWidth = mTexture->GetImage()->w / mColumns;
    const int clippedHeight = mTexture->GetImage()->h / mRows;
    
    const int clippedX = (index % mColumns) * clippedWidth;
    const int clippedY = ((index - (index % mColumns))/mColumns) * clippedHeight;

    mClippedRect.x = static_cast<float>(clippedX);
    mClippedRect.y = static_cast<float>(clippedY);
}

Vector VisualElement::GetOriginDisplacement()
{
    switch (mRectTransform.originAnchorPoint)
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
    return mIsClipped;
}

int VisualElement::GetSpriteIndex()
{
    return mSpriteIndex;
}

int VisualElement::GetColumns()
{
    return mColumns;
}

int VisualElement::GetRows()
{
    return mRows;
}

int VisualElement::GetSpriteSheetLength()
{
    return mSpriteSheetLength;
}

GPU_Rect* VisualElement::GetRenderRect()
{
    Vector originRenderPoint = GetOriginRenderPoint();
    
    GPU_Rect* transformedRect = new GPU_Rect
    {
        originRenderPoint.x,
        originRenderPoint.y,
        mRectTransform.Size.x * mRect.w,
        mRectTransform.Size.y * mRect.h
    };
    return transformedRect;
}

GPU_Rect* VisualElement::GetSrcRect()
{
    return (mIsClipped)? &mClippedRect:nullptr;
}

ImageQuad VisualElement::GetImageQuad()
{
    ImageQuad imageQuad
    {
        mTexture->GetImage(),
        GetSrcRect(),
        GetRenderRect()
    };
    return imageQuad;
}

Texture* VisualElement::GetTexture()
{
    return mTexture;
}

RectTransform* VisualElement::GetTransform()
{
    return &mRectTransform;
}
