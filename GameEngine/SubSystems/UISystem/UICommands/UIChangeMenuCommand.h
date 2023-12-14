#pragma once
#include "../UICommand.h"

class UIChangeMenuCommand : UICommand
{
public:
    ~UIChangeMenuCommand() override;
    void Execute(char* argument) override;
};
