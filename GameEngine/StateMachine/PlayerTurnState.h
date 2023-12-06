#pragma once
#include "game_state.h"

class player_turn_state : public game_state
{
public:

    player_turn_state();
    void DoState() override;
    void Begin() override;
    game_state* Finish(class game_state* currentState) override;
    void ProcessInput() override;
    static player_turn_state* get_player_state();
    static enemy_turn_state* get_enemy_state();
};
