#pragma once
#include <map>

#include "../SubSystem.h"
#include "TempUISystem/UInteractible_Temp.h"

class UIGroup;

class UISystem : public SubSystem
{
public:
    //Initializes variables
    UISystem();
    //Deallocates memory
    ~UISystem() override;

    void LateUpdate() override;
    //TODO: Most of our path sharing currently use const char pointers. Given what we want to do with data driven stuff, moving to a more flexible string class is probably better
    void SwitchMenu(const char* menuName);

    void ProcessEvent(int x, int y);
    UInteractible_Temp* TempMenuCreator(float xPosition, float yPosition, const char* path);
    void Free() override;
    //TODO: Most of our path sharing currently use const char pointers. Given what we want to do with data driven stuff, moving to a more flexible string class is probably better
    std::map<const char*, UIGroup*> uiGroups{};
    UIGroup* currentActiveGroup{};
};
