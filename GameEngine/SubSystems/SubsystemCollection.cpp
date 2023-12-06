#include "SubsystemCollection.h"

#include "SubSystem.h"

SubsystemCollection::SubsystemCollection()
{
    subsystems = std::map<int, SubSystem*>();
}

SubsystemCollection::~SubsystemCollection() = default;

void SubsystemCollection::IterateEarlyUpdate()
{
    for (auto it=subsystems.begin(); it!=subsystems.end(); ++it)
    {
        (it->second)->EarlyUpdate();
    }
}

void SubsystemCollection::IterateLateUpdate()
{
    for (auto it=subsystems.begin(); it!=subsystems.end(); ++it)
    {
        (it->second)->LateUpdate();
    }
}
