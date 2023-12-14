#include "UIGroup.h"

UIGroup::UIGroup() = default;

UIGroup::~UIGroup()
{
    VisualElements.clear();
    InteractableElements.clear();
}
