#pragma once

#include <list>

class UIInteractable;
class VisualElement;

class UIGroup
{
public:
    UIGroup();
    ~UIGroup();

    std::list<VisualElement*> visualElements{};
    std::list<UIInteractable*> interactableElements{};
};
