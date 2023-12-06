#include "PlayerTurnState.h"

#include <cstdio>

#include "enemy_turn_state.h"


player_turn_state::player_turn_state()
{
    printf("new player turn state");

}

void player_turn_state::DoState()
{

}

void player_turn_state::Begin()
{

}

game_state* player_turn_state::Finish(game_state* currentState)
{
    printf("Doing player turn");
    return master_state->get_enemy_state();
}

void player_turn_state::ProcessInput()
{

}

void player_turn_state::SetMasterState(game_state* master_game_state)
{
    printf("setting master state for player  state");

   master_state = master_game_state;
}
