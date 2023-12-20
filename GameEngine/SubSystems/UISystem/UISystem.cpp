#include "UISystem.h"

#include <SDL_gpu.h>

#include "UICommand.h"
#include "UIGroup.h"
#include "UIInteractable.h"
#include "../InputSystem.h"
#include "../SubsystemCollection.h"
#include "../VisualElementSubSystem.h"
#include "../../Global.h"
#include "TempUISystem/UInteractible_Temp.h"
#include "UICommands/UIAttackCommand.h"
#include "UICommands/UISwapPokemonCommand.h"
UInteractible_Temp* MenuPanel1;
UInteractible_Temp* MenuPanel2;


UISystem::UISystem()
{

    //TODO:Abysmal temporary interactable system. Better to get Petter when he doesn't have the flu to continue with his planned architecture. Everything with temp should be stripped out or folded into that
    MenuPanel1 = TempMenuCreator(0,120,"Resources/UISprites/Btn_Attack.png", new UIAttackCommand());
    MenuPanel2 = TempMenuCreator(160,120.,"Resources/UISprites/Btn_Swap.png", new UISwapPokemonCommand());
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
    MenuPanel1->ProcessEvent(x,y);
    MenuPanel2->ProcessEvent(x,y);
}

UInteractible_Temp* UISystem::TempMenuCreator(float xPosition, float yPosition, const char* path, UICommand* CommandToBind)
{
    RectTransform rect{
		        {xPosition,yPosition},
                {1,1},
                top_left,
                nullptr};
    VisualElement* menuPanelVisualElement = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>()->CreateVisualElement(path,rect,0,0,0);
     return new UInteractible_Temp(menuPanelVisualElement,new GPU_Rect(),CommandToBind);
}

void UISystem::Free()
{
    currentActiveGroup = nullptr;
    uiGroups.clear();
}

void UISystem::RegisterGameState(GameState* gameState)
{
    CurrentGameState = &gameState;
}
