#include "enemy_turn_state.h"

#include <cstdio>
#include <cstdlib>

#include "PlayerTurnState.h"

enemy_turn_state::enemy_turn_state()
{
    //printf("new enemy turn state");

}

enemy_turn_state::~enemy_turn_state()
= default;

void enemy_turn_state::DoState()
{

}


void enemy_turn_state::Begin()
{

}

game_state* enemy_turn_state::Finish(game_state* currentState)
{

    //printf("Doing enemy turn");
     return master_state->get_player_state();
}

void enemy_turn_state::ProcessInput()
{

}

void enemy_turn_state::SetMasterState(game_state* master_game_state)
{
    //printf("setting master state for enemy state");

    master_state = master_game_state;
}


