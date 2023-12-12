#include "UIInteractable.h"

#include "UICommand.h"

UIInteractable::UIInteractable(SDL_Rect* initBounds, VisualElement* initLinkedVisualElement, UICommand* initCommand, char* initCommandArgument)
{
    InteractBounds = initBounds;
    LinkedVisualElement = initLinkedVisualElement;
    InteractCommand = initCommand;
    InteractArgument = initCommandArgument;
}

bool UIInteractable::CheckInteracted(const SDL_Point* pointer, bool pressed)
{
    bool inside = SDL_PointInRect(pointer, InteractBounds);

    if(pressed && InteractCommand != nullptr)
    {
        InteractCommand->Execute(InteractArgument);
    }

    return inside;
}
