#include "PlayerTurnState.h"

#include <cstdio>

#include "enemy_turn_state.h"

player_turn_state::player_turn_state()
{
    printf("new player turn state");

}

void player_turn_state::DoState()
{


    
    if(input_system->input_data->action)
    {
        printf("Action was true");
        PrepareToExit = true;
    }
}

void player_turn_state::Begin()
{

}

game_state* player_turn_state::Finish(game_state* currentState)
{
    printf("Doing player turn");
   if(PrepareToExit)
   {
       PrepareToExit = false;
       return master_state->get_enemy_state();
   }
   else
   {
       return nullptr;
   }
}

void player_turn_state::ProcessInput()
{

}

void player_turn_state::SetMasterState(game_state* master_game_state)
{
    printf("setting master state for player  state");

   master_state = master_game_state;
}

bool player_turn_state::Enter()
{
    return true;
}
