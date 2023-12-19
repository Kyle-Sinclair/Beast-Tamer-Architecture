#pragma once

#include "SubSystem.h"

struct InputData
{
    int mouseX, mouseY;
    int moveX, moveY;
    bool action, back;
};

class InputSystem : public SubSystem
{
public:
    //Initializes variables
    InputSystem();
    //Deallocates memory
    ~InputSystem() override;

    void EarlyUpdate() override;

    InputData inputData{};
};
