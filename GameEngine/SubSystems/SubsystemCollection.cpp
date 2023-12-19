#include "SubsystemCollection.h"

#include "SubSystem.h"

SubsystemCollection::SubsystemCollection() = default;

SubsystemCollection::~SubsystemCollection() = default;

void SubsystemCollection::IterateEarlyUpdate()
{
    for (auto it = mSubsystems.begin(); it != mSubsystems.end(); ++it)
    {
        (it->second)->EarlyUpdate();
    }
}

void SubsystemCollection::IterateLateUpdate()
{
    for (auto system_iterator = mSubsystems.begin(); system_iterator != mSubsystems.end(); ++system_iterator)
    {
        (system_iterator->second)->LateUpdate();
    }
}

void SubsystemCollection::IterateFree()
{
    for (auto system_iterator = mSubsystems.begin(); system_iterator != mSubsystems.end(); ++system_iterator)
    {
        const auto system = (system_iterator->second);
        system->Free();
        delete system;
    }

    mSubsystems.clear();
}
