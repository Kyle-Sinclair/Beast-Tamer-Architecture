#include "game_state.h"

#include <cstdio>

#include "enemy_turn_state.h"
#include "PlayerTurnState.h"

game_state::game_state()
{
    input_system = gSubsystemCollection->GetSubSystem<InputSystem>();
    visual_element_sub_system = gSubsystemCollection->GetSubSystem<VisualElementSubSystem>();

}

void game_state::Begin()
{
    VisualElementSubSystem* subSystem = gSubsystemCollection->GetSubSystem<VisualElementSubSystem>();
    //Move this later,

    RectTransform playerSpriteRect{};
    
    PlayerPokemon = subSystem->CreateVisualElement("Resources/PokemonSprites/BackSprites.png",playerSpriteRect,0,25,16);
    PlayerPokemon->GetTransform()->originAnchorPoint = center;
    PlayerPokemon->GetTransform()->position.y = (INTERNAL_SCREEN_HEIGHT/2) + 16;
    PlayerPokemon->GetTransform()->position.x = 60;

    //printf("Position of pokemon sprite y: %d",PlayerPokemon->rectTransform.Position.y);
     RectTransform enemySpriteRect{};
     EnemyPokemon = subSystem->CreateVisualElement("Resources/PokemonSprites/Palmortis.png",enemySpriteRect,1,3,1);
     EnemyPokemon->GetTransform()->originAnchorPoint = center;
     EnemyPokemon->GetTransform()->position.y = INTERNAL_SCREEN_HEIGHT/4;
     EnemyPokemon->GetTransform()->position.x = (INTERNAL_SCREEN_WIDTH/2) + 52;
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
