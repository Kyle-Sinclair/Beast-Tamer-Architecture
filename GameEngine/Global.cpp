#include "Global.h"

#include "SubSystems/InputSystem.h"
#include "SubSystems/SubsystemCollection.h"

SubsystemCollection* gSubsystemCollection;

SDL_Window* gWindow{};

SDL_Renderer* gRenderer;

bool gQuit = false;
bool gWindowDirty = false;

bool InitGlobals()
{
    gSubsystemCollection = new SubsystemCollection();

    if (!gSubsystemCollection)
    {
        printf("No SubsystemCollection");
        return false;
    }
	
    gSubsystemCollection->gInputSystem = gSubsystemCollection->GetSubSystem<InputSystem>();

    if (!gSubsystemCollection->gInputSystem)
    {
        printf("No InputSystem");
        return false;
    }	

    return true;
}