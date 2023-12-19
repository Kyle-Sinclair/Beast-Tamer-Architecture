#pragma once


#include "../SubSystems/InputSystem.h"
#include "../SubSystems/VisualElementSubSystem.h"

class GameState
{
public:
    GameState();
    virtual ~GameState() = default;
    virtual void Begin();
    virtual void DoState();
    virtual GameState* Finish(class GameState* currentState);
    virtual void ProcessInput();

    class PlayerTurnState* GetPlayerState();
    class EnemyTurnState* GetEnemyState();
    
    bool SetPlayerState(PlayerTurnState* playerGameState);
    bool SetEnemyState(EnemyTurnState* enemyGameState);
    virtual void SetMasterState(GameState* masterGameState);
    virtual bool Enter();

    InputSystem* inputSystem;
    VisualElementSubSystem* visualElementSubSystem;
    bool shouldPrepareToExit = false;
private:

    VisualElement* mPlayerPokemon;
    VisualElement* mEnemyPokemon;
    
     PlayerTurnState* mPlayerGameState;
     EnemyTurnState* mEnemyGameState;
    
};

