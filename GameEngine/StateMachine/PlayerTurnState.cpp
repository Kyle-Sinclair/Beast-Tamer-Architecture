#include "PlayerTurnState.h"

#include <cstdio>

#include "enemy_turn_state.h"


player_turn_state::player_turn_state()
{
    printf("new player turn state");

}

void player_turn_state::DoState()
{
    game_state::DoState();
}

void player_turn_state::Begin()
{

}

game_state* player_turn_state::Finish(game_state* currentState)
{
    printf("Doing player turn");
    return get_enemy_state();
}

void player_turn_state::ProcessInput()
{
    game_state::ProcessInput();
}



player_turn_state* player_turn_state::get_player_state()
{
    return game_state::get_player_state();
}

enemy_turn_state* player_turn_state::get_enemy_state()
{

    return game_state::get_enemy_state();
}
