#include "VisualElementFactory.h"


VisualElementFactory::VisualElementFactory()
{
    textureLoader = new TextureLoader();
}

VisualElement* VisualElementFactory::CreateVisualElement(const char* path,RectTransform rectTransform,int spriteIndex,int columns, int rows)
{
    bool isNotClipped = (columns == 0 || rows == 0);
    Texture* texture = textureLoader->LoadTexture(path);
    VisualElement* visualElement;
    if(isNotClipped)
    {
        visualElement = new VisualElement(texture,rectTransform);
    }
    else
    {
        visualElement = new VisualElement(texture,spriteIndex,columns,rows,rectTransform);
    }
    visualElementSet.insert(visualElement);
    return visualElement;
 }
