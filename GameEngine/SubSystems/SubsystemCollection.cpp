#include "SubsystemCollection.h"

#include "SubSystem.h"
#include "SubsystemHelpers.h"

SubsystemCollection::SubsystemCollection()
{
    subsystems = std::map<int, SubSystem*>();
}

SubsystemCollection::~SubsystemCollection() = default;
