#include "VisualElementSubSystem.h"

#include "../Global.h"

VisualElementSubSystem::VisualElementSubSystem()
{
    factory = new VisualElementFactory();
    isDirty = false;
}

VisualElementSubSystem::~VisualElementSubSystem()
{
    delete factory;
}

void VisualElementSubSystem::SetBackground(int spriteIndex)
{
    RectTransform rect_transform;
    rect_transform.Position.x = INTERNAL_SCREEN_WIDTH/2;
    rect_transform.originAnchorPoint = Top;
    BackgoundVisualElement = factory->CreateVisualElement("Resources/PokemonSprites/Maps.png",rect_transform,spriteIndex,3,3);

    //Make factory create visual element set the dirty bool, it's better
    isDirty = true;
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

