#pragma once
#include "../UICommand.h"

class UISwapPokemonCommand : public UICommand
{
public:
    ~UISwapPokemonCommand() override;
    void Execute(char* argument) override;
    
};
