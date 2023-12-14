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
    std::list<VisualElement> CurrentNonBackgroundVisualElements;
    VisualElementFactory* factory;
    void EarlyUpdate() override;
    void LateUpdate() override;
    bool isDirty;
    bool HasBeenDirtied();
};
