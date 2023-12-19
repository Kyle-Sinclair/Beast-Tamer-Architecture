#include "UIGroup.h"

UIGroup::UIGroup() = default;

UIGroup::~UIGroup()
{
    visualElements.clear();
    interactableElements.clear();
}
