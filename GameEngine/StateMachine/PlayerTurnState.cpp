#include "PlayerTurnState.h"

#include <cstdio>

#include "enemy_turn_state.h"

player_turn_state::player_turn_state()
{
    printf("Now Player turn state");
}

void player_turn_state::DoState()
{
    game_state::DoState();
}

void player_turn_state::Begin()
{
    game_state::Begin();
}

game_state* player_turn_state::Finish()
{
    return new enemy_turn_state();
}

void player_turn_state::ProcessInput()
{
    game_state::ProcessInput();
}
