#include "EnemyTurnState.h"

#include <cstdio>
#include <cstdlib>

#include "PlayerTurnState.h"

EnemyTurnState::EnemyTurnState()
{
    //printf("new enemy turn state\n");

}

EnemyTurnState::~EnemyTurnState()
= default;

void EnemyTurnState::DoState()
{
    if(inputSystem->inputData.action)
    {
        shouldPrepareToExit = true;
    }
}


void EnemyTurnState::Begin()
{
    
}

GameState* EnemyTurnState::Finish(GameState* currentState)
{

   // printf("Doing enemy turn\n");
    if(shouldPrepareToExit)
    {
        shouldPrepareToExit = false;
        return mMasterState->GetPlayerState();
    }
    else
    {
        return nullptr;
    }
}

void EnemyTurnState::ProcessInput()
{

}

void EnemyTurnState::SetMasterState(GameState* masterGameState)
{
    printf("setting master state for enemy state \n");

    mMasterState = masterGameState;
}

bool EnemyTurnState::Enter()
{
    return false;
}

void EnemyTurnState::SwapPokemon()
{
    printf("cannot swap on enemy turn");
}


