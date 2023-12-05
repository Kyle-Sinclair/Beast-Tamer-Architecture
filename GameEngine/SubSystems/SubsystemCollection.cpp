#include "SubsystemCollection.h"

#include "SubSystem.h"
#include "SubsystemHelpers.h"

SubsystemCollection::SubsystemCollection()
{
    subsystems = std::map<int, SubSystem*>();
}

SubsystemCollection::~SubsystemCollection() = default;

template <class T>
T* SubsystemCollection::GetSubSystem()
{
    int hashCode = SubsystemHelpers::GetType<T>();
    
    if(!subsystems.contains(hashCode))
    {
        auto newSubSystem = new T();
        subsystems.insert(hashCode, newSubSystem);
    }
    
    return subsystems[SubsystemHelpers::GetType<T>()];
}
