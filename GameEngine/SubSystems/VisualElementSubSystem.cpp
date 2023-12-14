#include "VisualElementSubSystem.h"

VisualElementSubSystem::VisualElementSubSystem()
{
    factory = new VisualElementFactory();
}

VisualElementSubSystem::~VisualElementSubSystem()
{
    delete factory;
}

void VisualElementSubSystem::EarlyUpdate()
{
    SubSystem::EarlyUpdate();
}

void VisualElementSubSystem::LateUpdate()
{
    SubSystem::LateUpdate();
}
