#include "Global.h"

#include "SubSystems/InputSystem.h"
#include "SubSystems/SubsystemCollection.h"

SubsystemCollection* gSubsystemCollection;

SDL_Window* gWindow{};

SDL_Renderer* gRenderer;

bool gQuit = false;
bool gWindowDirty = false;