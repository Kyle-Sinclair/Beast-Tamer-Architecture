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
        int hashCode = SubsystemHelpers::GetType<T>();
    
        if(!subsystems.contains(hashCode))
        {
            auto newSubSystem = static_cast<SubSystem*>(new T());
            subsystems.insert_or_assign(hashCode, newSubSystem);
        }
    
        return static_cast<T*>(subsystems[SubsystemHelpers::GetType<T>()]);
    }

private:
    std::map<int, SubSystem*> subsystems;
};
