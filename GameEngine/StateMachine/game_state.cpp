#include "game_state.h"

#include <cstdio>

#include "enemy_turn_state.h"
#include "PlayerTurnState.h"

game_state::game_state()
{
}

void game_state::Begin()
{
}

void game_state::DoState()
{
}

game_state* game_state::Finish(game_state* currentState)
{
    //printf("Doing generic turn");
    return get_player_state();
}

void game_state::ProcessInput()
{
}


player_turn_state* game_state::get_player_state()
{
    return player_game_state;
}

enemy_turn_state* game_state::get_enemy_state()
{

    return enemy_game_state;
}

bool game_state::set_player_state(player_turn_state* newplayer_state)
{
    player_game_state = newplayer_state;
    player_game_state->SetMasterState(this);
    return true;
}

bool game_state::set_enemy_state(enemy_turn_state* newenemy_state)
{
    enemy_game_state = newenemy_state;
    enemy_game_state->SetMasterState(this);
    return true;

}

void game_state::SetMasterState(game_state* master_game_state)
{
}

bool game_state::Enter()
{
    return true;
}
