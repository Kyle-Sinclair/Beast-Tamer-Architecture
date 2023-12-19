#include "UIInteractable.h"

#include "UICommand.h"
#include "../../SpriteLoader/VisualElement.h"

UIInteractable::UIInteractable(SDL_Rect* initBounds, VisualElement* initLinkedVisualElement, UICommand* initCommand, char* initCommandArgument)
{
    interactBounds = initBounds;
    linkedVisualElement = initLinkedVisualElement;
    interactCommand = initCommand;
    interactArgument = initCommandArgument;
}

bool UIInteractable::CheckInteracted(const SDL_Point pointer, const bool pressed)
{
    const bool inside = SDL_PointInRect(&pointer, interactBounds);

    if(pressed && interactCommand != nullptr)
    {
        interactCommand->Execute(interactArgument);
    }

    return inside;
}
