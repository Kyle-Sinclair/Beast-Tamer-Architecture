#pragma once
#include "../UICommand.h"

class UIAttackCommand : public UICommand
{
public:
    ~UIAttackCommand() override;
    void Execute(char* argument) override;
};
