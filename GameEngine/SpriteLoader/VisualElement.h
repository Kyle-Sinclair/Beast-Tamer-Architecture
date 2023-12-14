#pragma once

#include <SDL_render.h>

#include "RectTransform.h"
#include "TextureLoader.h"
enum DrawMode
{
    Simple,
    Sliced
};
struct DrawModeData
{
    int TopLeft = 0;
    int TopRight = 0;
    int BottomLeft = 0;
    int BottomRight = 0;
};

class VisualElement
{
    GPU_Rect rect;
    GPU_Rect clippedRect;
    RectTransform rectTransform;
    
    bool isClipped;
    int spriteIndex;
    int columns;
    int rows;
    int spriteSheetLength = 0;

    Texture* texture;
    Vector GetOriginDisplacement();
public:
    //Renderer and texture are switched to avoid ambigous function calls;
    VisualElement(Texture* texture,RectTransform rectTransform);
    VisualElement(Texture* texture,int spriteIndex,int columns, int rows,RectTransform rectTransform);
    Vector GetOriginRenderPoint();
    void SetSpriteIndex(int index);
    //void Render();

    bool IsClipped();
    int GetSpriteIndex();
    int GetColumns();
    int GetRows();
    int GetSpriteSheetLength();

    GPU_Rect* GetRenderRect();
    GPU_Rect* GetSrcRect();
    Texture* GetTexture();
    DrawMode drawMode = Simple;
    DrawModeData drawModeData; 
};
