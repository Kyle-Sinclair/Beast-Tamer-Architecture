#pragma once
#include "GameState.h"

class EnemyTurnState : public GameState
{
public:
    EnemyTurnState();
    ~EnemyTurnState() override;

    void DoState() override;
    void Begin() override;
    GameState* Finish(class GameState* currentState) override;
    void ProcessInput() override;
    void SetMasterState(GameState* masterGameState) override;
    bool Enter() override;

private:

    GameState* mMasterState;
};
