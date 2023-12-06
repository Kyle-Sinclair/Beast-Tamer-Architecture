#pragma once


class game_state
{
public:
    game_state();
    virtual ~game_state() = default;
    virtual void Begin();
    virtual void DoState();
    virtual game_state* Finish(class game_state* currentState);
    virtual void ProcessInput();

    static class player_turn_state* get_player_state();
    static class enemy_turn_state* get_enemy_state();
    
    bool set_player_state(player_turn_state* player_game_state);
    bool set_enemy_state(enemy_turn_state* enemy_game_state);
private:
    
  
    static player_turn_state* player_game_state;
   static  enemy_turn_state* enemy_game_state;
    
};

