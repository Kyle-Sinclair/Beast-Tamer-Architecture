#pragma once

class game_state
{
public:
    game_state() = default;
    virtual ~game_state() = default;
    virtual void Begin();
    virtual void DoState();
    virtual game_state* Finish();
    virtual void ProcessInput();
    
};

