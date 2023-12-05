#pragma once
#include "game_state.h"

class enemy_turn_state : public game_state
{
public:
    enemy_turn_state();
    ~enemy_turn_state() override = default;

    void DoState() override;
    void Begin() override;
    game_state* Finish() override;
    void ProcessInput() override;
};
