#include "SubsystemCollection.h"

#include "SubSystem.h"

SubsystemCollection::SubsystemCollection() = default;

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

void SubsystemCollection::IterateFree()
{
    for (auto it=subsystems.begin(); it!=subsystems.end(); ++it)
    {
        const auto system = (it->second);
        system->Free();
        delete system;
    }

    subsystems.clear();
}
