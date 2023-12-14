#pragma once
#include "game_state.h"

class enemy_turn_state : public game_state
{
public:
    enemy_turn_state();
    ~enemy_turn_state() override;

    void DoState() override;
    void Begin() override;
    game_state* Finish(class game_state* currentState) override;
    void ProcessInput() override;
    void SetMasterState(game_state* master_game_state) override;
    bool Enter() override;

private:

    game_state* master_state;
};
