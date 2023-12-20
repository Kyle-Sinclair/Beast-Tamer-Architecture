#include "UISystem.h"

#include <SDL_gpu.h>

#include "UIGroup.h"
#include "UIInteractable.h"
#include "../InputSystem.h"
#include "../SubsystemCollection.h"
#include "../VisualElementSubSystem.h"
#include "../../Global.h"
#include "TempUISystem/UInteractible_Temp.h"
UInteractible_Temp* MenuPanel;


UISystem::UISystem()
{
  MenuPanel = TempMenuCreator();
};

UISystem::~UISystem() = default;

void UISystem::LateUpdate()
{
    const InputData input_data = SUBSYSTEM_COLLECTION->gInputSystem->inputData;

    const SDL_Point mouse_pointer = SDL_Point{input_data.mouseX, input_data.mouseY};

/*
    if (currentActiveGroup != nullptr)
    {
        for (UIInteractable* const interactable : currentActiveGroup->interactableElements)
        {
            interactable->CheckInteracted(mouse_pointer, input_data.action);
        }
    }
    */
}

void UISystem::SwitchMenu(const char* menuName)
{
    for (auto group_iterator = uiGroups.begin(); group_iterator != uiGroups.end(); ++group_iterator)
    {
        if (strcmp(group_iterator->first, menuName) == 0)
        {
            currentActiveGroup = group_iterator->second;
        }
    }
}

void UISystem::ProcessEvent(int x, int y)
{
    MenuPanel->ProcessEvent(x,y);
}

UInteractible_Temp* UISystem::TempMenuCreator()
{
    RectTransform rect{
		        {100,100},
                {10,3},
                top_left,
                nullptr};
    VisualElement* menuPanelVisualElement = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>()->CreateVisualElement("Resources/UISprites/MenuBack.png",rect,0,0,0);

     return new UInteractible_Temp(menuPanelVisualElement,new GPU_Rect() );
}

void UISystem::Free()
{
    currentActiveGroup = nullptr;
    uiGroups.clear();
}
