#include "enemy_turn_state.h"

#include <cstdio>
#include <cstdlib>

#include "PlayerTurnState.h"

enemy_turn_state::enemy_turn_state()
{
    printf("new enemy turn state");

}

enemy_turn_state::~enemy_turn_state()
= default;

void enemy_turn_state::DoState()
{
    game_state::DoState();
}


void enemy_turn_state::Begin()
{
    game_state::Begin();
}

game_state* enemy_turn_state::Finish(game_state* currentState)
{

    printf("Doing enemy turn");
     return get_player_state();
}

void enemy_turn_state::ProcessInput()
{
    game_state::ProcessInput();
}


player_turn_state* enemy_turn_state::get_player_state()
{
    return game_state::get_player_state();
}

enemy_turn_state* enemy_turn_state::get_enemy_state()
{
    return game_state::get_enemy_state();
}
