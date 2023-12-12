#pragma once
#include <map>

#include "../SubSystem.h"

class UIGroup;

class UISystem : public SubSystem
{
public:
    //Initializes variables
    UISystem();
    //Deallocates memory
    ~UISystem() override;

    void LateUpdate() override;

    void SwitchMenu(const char* menuName);
    
    void Free() override;

    std::map<const char*, UIGroup*> UIGroups{};
    UIGroup* CurrentActiveGroup{};
};
