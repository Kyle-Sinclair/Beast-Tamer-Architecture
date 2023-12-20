#include "GameState.h"

#include <cstdio>

#include "EnemyTurnState.h"
#include "PlayerTurnState.h"

GameState::GameState()
{
    inputSystem = SUBSYSTEM_COLLECTION->GetSubSystem<InputSystem>();
    visualElementSubSystem = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>();
}

void GameState::Begin()
{
    VisualElementSubSystem* sub_system = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>();
    //Move this later,
    RectTransform player_sprite_rect{};
    
    mPlayerPokemon = sub_system->CreateVisualElement("Resources/PokemonSprites/BackSprites.png",player_sprite_rect,0,25,16);
    mPlayerPokemon->GetTransform()->originAnchorPoint = center;
    mPlayerPokemon->GetTransform()->position.y = (INTERNAL_SCREEN_HEIGHT/2);
    mPlayerPokemon->GetTransform()->position.x = 60;

    //printf("Position of pokemon sprite y: %d",PlayerPokemon->rectTransform.Position.y);
     RectTransform enemy_sprite_rect{};
     mEnemyPokemon = sub_system->CreateVisualElement("Resources/PokemonSprites/Palmortis.png",enemy_sprite_rect,1,3,1);
     mEnemyPokemon->GetTransform()->originAnchorPoint = center;
     mEnemyPokemon->GetTransform()->position.y = INTERNAL_SCREEN_HEIGHT/4;
     mEnemyPokemon->GetTransform()->position.x = (INTERNAL_SCREEN_WIDTH/2) + 52;
  
}

void GameState::DoState()
{
}

GameState* GameState::Finish(GameState* currentState)
{
    //printf("Doing generic turn");
    return GetPlayerState();
}

void GameState::ProcessInput()
{
}


PlayerTurnState* GameState::GetPlayerState()
{
    return mPlayerGameState;
}

EnemyTurnState* GameState::GetEnemyState()
{

    return mEnemyGameState;
}

bool GameState::SetPlayerState(PlayerTurnState* newPlayerState)
{
    mPlayerGameState = newPlayerState;
    mPlayerGameState->SetMasterState(this);
    return true;
}

bool GameState::SetEnemyState(EnemyTurnState* newEnemyState)
{
    mEnemyGameState = newEnemyState;
    mEnemyGameState->SetMasterState(this);
    return true;

}

void GameState::SetMasterState(GameState* masterGameState)
{
}

bool GameState::Enter()
{
    return true;
}
