#include "PlayerTurnState.h"

#include <cstdio>

#include "EnemyTurnState.h"

PlayerTurnState::PlayerTurnState()
{
}

void PlayerTurnState::DoState()
{
    if(inputSystem->inputData.action)
    {
        shouldPrepareToExit = true;
    }
}

void PlayerTurnState::Begin()
{
    visualElementSubSystem->SetBackground(0);
}

GameState* PlayerTurnState::Finish(GameState* currentState)
{
   // printf("Doing player turn\n");
   if(shouldPrepareToExit)
   {
       shouldPrepareToExit = false;
       return mMasterState->GetEnemyState();
   }
   else
   {
       return nullptr;
   }
}

void PlayerTurnState::ProcessInput()
{

}

void PlayerTurnState::SetMasterState(GameState* masterGameState)
{
   // printf("setting master state for player  state\n");

   mMasterState = masterGameState;
}

bool PlayerTurnState::Enter()
{
    return true;
}

void PlayerTurnState::SwapPokemon()
{
    GameState::SwapPokemon();
}
