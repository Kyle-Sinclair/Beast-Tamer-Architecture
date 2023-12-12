#pragma once
#include <map>

#include "SubsystemHelpers.h"

class SubSystem;

class SubsystemCollection
{
public:
    SubsystemCollection();
    ~SubsystemCollection();

    template<class T>
    T* GetSubSystem()
    {
        const int hashCode = SubsystemHelpers::GetType<T>();
    
        if(!subsystems.contains(hashCode))
        {
            SubSystem* newSubSystem = dynamic_cast<SubSystem*>(new T());
            subsystems.insert_or_assign(hashCode, newSubSystem);
        }
    
        return dynamic_cast<T*>(subsystems[SubsystemHelpers::GetType<T>()]);
    }

    void IterateEarlyUpdate();
    void IterateLateUpdate();
    void IterateFree();

    //Important and common so have fixed pointer
    class InputSystem* gInputSystem{};

private:
    std::map<int, SubSystem*> subsystems{};
};
