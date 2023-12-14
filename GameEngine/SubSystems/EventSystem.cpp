#include "EventSystem.h"

EventSystem::EventSystem()
= default;

EventSystem::~EventSystem()
= default;

void EventSystem::EarlyUpdate()
{
    SubSystem::EarlyUpdate();

}

void EventSystem::LateUpdate()
{
}
