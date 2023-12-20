#include "UIAttackCommand.h"

UIAttackCommand::~UIAttackCommand()
{
}

void UIAttackCommand::Execute(char* argument)
{
    //TODO:This would be a good area to start making the game state machine also a subsystem, and then bind commands that tie directly to it from here.
    printf("Attacking!");
}
