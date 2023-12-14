#include "UISystem.h"

#include "UIGroup.h"
#include "UIInteractable.h"
#include "../InputSystem.h"
#include "../SubsystemCollection.h"
#include "../../Global.h"

UISystem::UISystem() = default;

UISystem::~UISystem() = default;

void UISystem::LateUpdate()
{
    const auto inputData = gSubsystemCollection->gInputSystem->input_data;

    auto mousePointer = SDL_Point(inputData.mouse_x, inputData.mouse_y);

    if(CurrentActiveGroup != nullptr)
    {
        for (auto interactable : CurrentActiveGroup->InteractableElements)
        {
            interactable->CheckInteracted(mousePointer, inputData.action);
        }        
    }
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

void UISystem::Free()
{
    CurrentActiveGroup = nullptr;
    UIGroups.clear();
}
