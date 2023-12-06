#pragma once
#ifndef InputSystem_h
#define InputSystem_h

typedef struct Input_Data
{
    int mouse_x, mouse_y;
    int move_x, move_y;
    bool action, back;
} Input_Data;

class InputSystem
{
public:
    //Initializes variables
    InputSystem();
    //Deallocates memory
    ~InputSystem();

    void UpdateInputs();

    Input_Data* input_data;
};

#endif
