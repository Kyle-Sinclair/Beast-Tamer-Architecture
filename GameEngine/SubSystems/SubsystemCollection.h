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
    
        if(!mSubsystems.contains(hashCode))
        {
            SubSystem* new_sub_system = dynamic_cast<SubSystem*>(new T());
            mSubsystems.insert_or_assign(hashCode, new_sub_system);
        }
    
        return dynamic_cast<T*>(mSubsystems[SubsystemHelpers::GetType<T>()]);
    }

    void IterateEarlyUpdate();
    void IterateLateUpdate();
    void IterateFree();

    //Important and common so have fixed pointer
    class InputSystem* inputSystem{};

private:
    std::map<int, SubSystem*> mSubsystems{};
};
