#pragma once
#include "game_state.h"

class player_turn_state : public game_state
{
public:
    player_turn_state();
    
    void DoState() override;
    void Begin() override;
    game_state* Finish() override;
    void ProcessInput() override;
};
