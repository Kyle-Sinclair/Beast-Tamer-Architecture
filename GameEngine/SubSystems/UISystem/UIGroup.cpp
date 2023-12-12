#include "UIGroup.h"

#include "UIInteractable.h"
#include "../../SpriteLoader/VisualElement.h"

UIGroup::UIGroup() = default;

UIGroup::~UIGroup()
{
    VisualElements.clear();
    InteractableElements.clear();
}
