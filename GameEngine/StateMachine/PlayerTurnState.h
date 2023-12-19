#pragma once
#include "game_state.h"

#include "../Global.h"
#include "../SubSystems/SubsystemCollection.h"

class player_turn_state : public game_state
{
public:
    void SetMasterState(game_state* master_game_state) override;

    player_turn_state();
    void DoState() override;
    void Begin() override;
    game_state* Finish(class game_state* currentState) override;
    void ProcessInput() override;


    bool Enter() override;

private:
    game_state* master_state;
   

  
};
