#include "VisualElementFactory.h"


VisualElementFactory::VisualElementFactory()
{
    textureLoader = new TextureLoader();
}
//TODO: Most of our path sharing currently use const char pointers. Given what we want to do with data driven stuff, moving to a more flexible string class is probably better
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
