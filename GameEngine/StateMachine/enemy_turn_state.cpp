#include "enemy_turn_state.h"

#include <cstdio>
#include <cstdlib>

#include "PlayerTurnState.h"

enemy_turn_state::enemy_turn_state()
{
    printf("Now enemy turn state");
}

void enemy_turn_state::DoState()
{
    game_state::DoState();
}


void enemy_turn_state::Begin()
{
    game_state::Begin();
}

game_state* enemy_turn_state::Finish()
{
    return new player_turn_state();

}

void enemy_turn_state::ProcessInput()
{
    game_state::ProcessInput();
}
