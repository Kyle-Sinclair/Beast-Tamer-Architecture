#pragma once
#include "SubSystem.h"

class EventSystem : public SubSystem
{
public:
    EventSystem();
    ~EventSystem() override;
    void EarlyUpdate() override;
    void LateUpdate() override;
};
