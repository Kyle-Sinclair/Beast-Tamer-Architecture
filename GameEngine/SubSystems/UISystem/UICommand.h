#pragma once
#include <string>

class UICommand
{
public:
    virtual ~UICommand();
    virtual void Execute(char* argument);
};
