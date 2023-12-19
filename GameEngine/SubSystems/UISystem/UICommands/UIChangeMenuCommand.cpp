#include "UIChangeMenuCommand.h"

#include "../UISystem.h"
#include "../../SubsystemCollection.h"
#include "../../../Global.h"

UIChangeMenuCommand::~UIChangeMenuCommand()
{
}

void UIChangeMenuCommand::Execute(char* argument)
{
    UISystem* uiSystem = SUBSYSTEM_COLLECTION->GetSubSystem<UISystem>();

    uiSystem->SwitchMenu(argument);
}
