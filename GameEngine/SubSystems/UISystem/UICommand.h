#pragma once

class UICommand
{
public:
    virtual ~UICommand();
    virtual void Execute(char* argument);
};
