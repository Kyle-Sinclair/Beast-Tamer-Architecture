#pragma once

#include "SubSystem.h"

typedef struct Input_Data
{
    int mouse_x, mouse_y;
    int move_x, move_y;
    bool action, back;
} Input_Data;

class InputSystem : public SubSystem
{
public:
    //Initializes variables
    InputSystem();
    //Deallocates memory
    ~InputSystem() override;

    void EarlyUpdate() override;

    Input_Data* input_data;
};
