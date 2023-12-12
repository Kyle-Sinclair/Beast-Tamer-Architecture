#pragma once
#include <list>

class UIInteractable;
class VisualElement;

class UIGroup
{
public:
    UIGroup();
    ~UIGroup();

    std::list<VisualElement> VisualElements{};
    std::list<UIInteractable> InteractableElements{};
};
