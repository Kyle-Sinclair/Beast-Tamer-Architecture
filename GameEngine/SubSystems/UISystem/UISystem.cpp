#include "UISystem.h"

#include <SDL_gpu.h>

#include "UIGroup.h"
#include "UIInteractable.h"
#include "../InputSystem.h"
#include "../SubsystemCollection.h"
#include "../VisualElementSubSystem.h"
#include "../../Global.h"
#include "TempUISystem/UInteractible_Temp.h"
UInteractible_Temp* MenuPanel1;
UInteractible_Temp* MenuPanel2;


UISystem::UISystem()
{
  MenuPanel1 = TempMenuCreator(0,120,"Resources/UISprites/Btn_Attack.png");
    MenuPanel2 = TempMenuCreator(120,120.,"Resources/UISprites/Btn_Swap.png");
};

UISystem::~UISystem() = default;

void UISystem::LateUpdate()
{
    const InputData input_data = SUBSYSTEM_COLLECTION->inputSystem->inputData;

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
    MenuPanel1->ProcessEvent(x,y);
    MenuPanel2->ProcessEvent(x,y);
}

UInteractible_Temp* UISystem::TempMenuCreator(float xPosition, float yPosition, const char* path)
{
    RectTransform rect{
		        {xPosition,yPosition},
                {1,1},
                top_left,
                nullptr};
    VisualElement* menuPanelVisualElement = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>()->CreateVisualElement(path,rect,0,0,0);

     return new UInteractible_Temp(menuPanelVisualElement,new GPU_Rect() );
}

void UISystem::Free()
{
    currentActiveGroup = nullptr;
    uiGroups.clear();
}
