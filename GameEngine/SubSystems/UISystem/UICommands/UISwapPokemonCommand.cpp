#include "UISwapPokemonCommand.h"

#include "../UISystem.h"
#include "../../SubsystemCollection.h"
#include "../../VisualElementSubSystem.h"
#include "../../../Global.h"
#include "../../../SpriteLoader/VisualElement.h"

class UISystem;

UISwapPokemonCommand::~UISwapPokemonCommand()
{
}

void UISwapPokemonCommand::Execute(char* argument)
{
    VisualElementSubSystem* visual_element_system = SUBSYSTEM_COLLECTION->GetSubSystem<VisualElementSubSystem>();
    visual_element_system->SwapPokemonSprites();
}
