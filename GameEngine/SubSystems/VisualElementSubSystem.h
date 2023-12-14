#pragma once
#include "../SpriteLoader/VisualElementFactory.h"
#include "../SubSystems/SubSystem.h"

class VisualElementSubSystem: public SubSystem
{
public:
    VisualElementSubSystem();
    ~VisualElementSubSystem() override;
    VisualElementFactory* factory;
    void EarlyUpdate() override;
    void LateUpdate() override;
};
