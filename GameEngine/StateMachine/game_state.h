#pragma once


#include "../SubSystems/InputSystem.h"
#include "../SubSystems/VisualElementSubSystem.h"

class game_state
{
public:
    game_state();

    
    virtual void Begin();
    virtual void DoState();
    virtual game_state* Finish(class game_state* currentState);
    
    virtual void ProcessInput();

    class player_turn_state* get_player_state();
    class enemy_turn_state* get_enemy_state();
   

    InputSystem* input_system;
    VisualElementSubSystem* visual_element_sub_system;
    bool PrepareToExit = false;
    virtual ~game_state() = default;

    bool set_player_state(player_turn_state* player_game_state);
    bool set_enemy_state(enemy_turn_state* enemy_game_state);
    virtual void SetMasterState(game_state* master_game_state);
    virtual bool Enter();
private:

    VisualElement* PlayerPokemon;
    VisualElement* EnemyPokemon;
    
    player_turn_state* player_game_state;
    enemy_turn_state* enemy_game_state;
    
};

