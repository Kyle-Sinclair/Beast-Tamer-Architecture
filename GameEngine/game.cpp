//Using SDL and standard IO
#include <list>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <xstring>

#include "StateMachine/EnemyTurnState.h"
#include "Global.h"
#include "SpriteLoader/VisualElementFactory.h"
#include "StateMachine/PlayerTurnState.h"
#include "StateMachine/GameState.h"
#include "SubSystems/InputSystem.h"
#include "SubSystems/SubsystemCollection.h"
#include "RenderEngine/RenderEngine.h"

InputSystem* inputSystem;
GameState *CurrentGameState;
VisualElement* VisualElements[2];
Uint32 msLast;

bool Init();
bool InitGlobals();
void Update(float deltaTime);
void Close();

int main(int argc, char* args[])
{
	//Flag setting
	Init();

	//Update Loop
	while (SHOULD_QUIT == false)
	{
		//Early
		SUBSYSTEM_COLLECTION->IterateEarlyUpdate();
		
		CurrentGameState->Begin();
		CurrentGameState->DoState();
		GameState* NewGameState = CurrentGameState->Finish(CurrentGameState);
		if(NewGameState != nullptr)
		{
			CurrentGameState = NewGameState;
		}
		//Late. Might move order
		RenderEngine::PreRenderCheck();
		SUBSYSTEM_COLLECTION->IterateLateUpdate();
	// Tick
		const Uint32 msCurrent = SDL_GetTicks();
		const Uint32 msDelta = msCurrent - msLast;
		msLast = msCurrent;

		// Draw and present

		RenderEngine::Render();

		//todo lazy fps cap fix later plz
		SDL_Delay(1000/SCREEN_FPS); // can be used to wait for a certain amount of ms
	}
	
	Close();
	return 0;
}

void Update(float deltaTime)
{
/*TODO:Perhaps we can compress the updating while loop into it's own method as well. Could be used to pass global parameters/objects in for reverse
  dependency injection for example
*/
	
}

bool Init()
{
	
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	// initialize SDL_ttf for font loading
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Start up SDL and create window
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	//RenderEngine::Init();
	InitGlobals();

	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");  // no smoothing pixel art.
	//SDL_RenderSetLogicalSize(RENDERER, INTERNAL_SCREEN_WIDTH, INTERNAL_SCREEN_HEIGHT);
	
	printf("Initialising called\n");
	return true;
}

bool InitGlobals()
{
	SUBSYSTEM_COLLECTION = new SubsystemCollection();

	if (!SUBSYSTEM_COLLECTION)
	{
		printf("No SubsystemCollection");
		return false;
	}
	
	inputSystem = SUBSYSTEM_COLLECTION->GetSubSystem<InputSystem>();

	if (!inputSystem)
	{
		printf("No InputSystem");
		return false;
	}
	RenderEngine::Init();
	CurrentGameState = new GameState();
	CurrentGameState->SetEnemyState(new EnemyTurnState());
	CurrentGameState->SetPlayerState(new PlayerTurnState());
	CurrentGameState->Begin();
	GameState* NewGameState = 	CurrentGameState->Finish(CurrentGameState);
	if(NewGameState != nullptr)
	{
		//printf("updating state");
		CurrentGameState = NewGameState;
	}
	else
	{
		printf("null state");

	}
	return true;
	
}

void Close()
{
	//SDL_DestroyRenderer(RENDERER); RENDERER = nullptr;
	//SDL_DestroyWindow(WINDOW); WINDOW = nullptr;
	
	RenderEngine::Quit();
	GPU_Quit();
	IMG_Quit();
	SDL_Quit();
}
