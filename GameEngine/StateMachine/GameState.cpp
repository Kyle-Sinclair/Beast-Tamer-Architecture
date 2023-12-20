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
    sub_system->CreateBattleSprites();

  
}

void GameState::DoState()
{
}

GameState* GameState::Finish(GameState* currentState)
{
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

void GameState::SwapPokemon()
{
    printf("Swapping pokemon");
}
