#include "UISystem.h"

UISystem::UISystem()
{
    UIGroups = std::map<char*, UIGroup*>();
    CurrentActiveGroup = nullptr;
}

UISystem::~UISystem()
{
}

void UISystem::LateUpdate()
{
    SubSystem::LateUpdate();

    
}

void UISystem::SwitchMenu(const char* menuName)
{
    for (auto it=UIGroups.begin(); it!=UIGroups.end(); ++it)
    {
        if(strcmp(it->first, menuName) == 0)
        {
            CurrentActiveGroup = it->second;
        }
    }
}
