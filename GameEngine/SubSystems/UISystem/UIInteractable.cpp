#include "UIInteractable.h"

#include "UICommand.h"
#include "../../SpriteLoader/VisualElement.h"

UIInteractable::UIInteractable(SDL_Rect* initBounds, VisualElement* initLinkedVisualElement, UICommand* initCommand, char* initCommandArgument)
{
    InteractBounds = initBounds;
    LinkedVisualElement = initLinkedVisualElement;
    InteractCommand = initCommand;
    InteractArgument = initCommandArgument;
}

bool UIInteractable::CheckInteracted(const SDL_Point pointer, const bool pressed)
{
    const bool inside = SDL_PointInRect(&pointer, InteractBounds);

    if(pressed && InteractCommand != nullptr)
    {
        InteractCommand->Execute(InteractArgument);
    }

    return inside;
}
