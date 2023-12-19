#include "VisualElementSubSystem.h"

#include "../Global.h"

VisualElementSubSystem::VisualElementSubSystem()
{
    factory = new VisualElementFactory();
    isDirty =false;
}

VisualElementSubSystem::~VisualElementSubSystem()
{
    delete factory;
}

void VisualElementSubSystem::SetBackground(int spriteIndex)
{
    RectTransform rect_transform;
    rect_transform.position.x = INTERNAL_SCREEN_WIDTH/2;
    rect_transform.originAnchorPoint = top;
    BackgoundVisualElement = factory->CreateVisualElement("Resources/PokemonSprites/Maps.png",rect_transform,spriteIndex,3,3);

    //Make factory create visual element set the dirty bool, it's better
    isDirty = true;
}

VisualElement* VisualElementSubSystem::CreateVisualElement(const char* path, RectTransform rectTransform, int spriteIndex, int columns, int rows)
{
    VisualElement* visualElement = factory->CreateVisualElement(path,rectTransform,spriteIndex,columns,rows);
    CurrentNonBackgroundVisualElements.push_back(visualElement);
    return visualElement;
}

void VisualElementSubSystem::EarlyUpdate()
{
    SubSystem::EarlyUpdate();
    isDirty = false;
}

void VisualElementSubSystem::LateUpdate()
{
    SubSystem::LateUpdate();
}

bool VisualElementSubSystem::HasBeenDirtied()
{
    return isDirty;
}

