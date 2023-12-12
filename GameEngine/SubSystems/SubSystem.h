#pragma once

class SubSystem
{
public:
    virtual ~SubSystem() = default;
    
    virtual void EarlyUpdate();

    virtual void LateUpdate();

    virtual void Free();
};
