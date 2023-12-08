#include "VisualElementFactory.h"

VisualElementFactory::VisualElementFactory(SDL_Renderer* renderer)
{
    textureLoader = new TextureLoader(renderer);
    this->renderer = renderer;
}

VisualElement* VisualElementFactory::CreateVisualElement(const char* path, int x,int y,int w,int h,int spriteIndex,int columns, int rows)
{

    
    bool isNotClipped = (columns == 0 || rows == 0);
    Texture* texture = textureLoader->LoadTexture(path);
    VisualElement* visualElement;
    if(isNotClipped)
    {
        visualElement = new VisualElement(renderer,texture,w,h,x,y);
    }
    else
    {
        visualElement = new VisualElement(texture,renderer,spriteIndex,columns,rows,w,h,x,y);
    }
    VisualElementSet.insert(visualElement);
    return visualElement;
}
