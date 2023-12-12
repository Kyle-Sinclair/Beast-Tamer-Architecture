#include "UIGroup.h"

UIGroup::UIGroup()
{
    VisualElements = std::list<VisualElement>();
    InteractableElements = std::list<UIInteractable>();
}

UIGroup::~UIGroup()
{
    VisualElements.clear();
    InteractableElements.clear();
}
