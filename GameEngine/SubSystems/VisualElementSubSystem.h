#pragma once
#include "../SpriteLoader/VisualElementFactory.h"
#include "../SubSystems/SubSystem.h"

class VisualElementSubSystem: public SubSystem
{
public:
    VisualElementSubSystem();
    ~VisualElementSubSystem() override;
    void SetBackground(int spriteIndex);
    VisualElement* BackgoundVisualElement;
    std::list<VisualElement*> CurrentNonBackgroundVisualElements;
    VisualElementFactory* factory;
    VisualElement* CreateVisualElement(const char* path,RectTransform rectTransform = RectTransform(),int spriteIndex = 0,int columns = 0, int rows = 0);
    void EarlyUpdate() override;
    void LateUpdate() override;
    bool isDirty;
    bool HasBeenDirtied();
};
