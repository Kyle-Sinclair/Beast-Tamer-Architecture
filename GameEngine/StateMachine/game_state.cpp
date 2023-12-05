#include "game_state.h"

#include "PlayerTurnState.h"

void game_state::Begin()
{
}

void game_state::DoState()
{
}

game_state* game_state::Finish()
{
    return new player_turn_state;
}

void game_state::ProcessInput()
{
}
