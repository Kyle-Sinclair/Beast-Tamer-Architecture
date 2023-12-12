#pragma once
#include <SDL_rect.h>

class UICommand;
class VisualElement;

class UIInteractable
{
public:
    UIInteractable(SDL_Rect* initBounds, VisualElement* initLinkedVisualElement, UICommand* initCommand, char* initCommandArgument);
    SDL_Rect* InteractBounds{};
    VisualElement* LinkedVisualElement{};

    UICommand* InteractCommand{};
    char* InteractArgument{};

    bool CheckInteracted(SDL_Point pointer, bool pressed);
};
