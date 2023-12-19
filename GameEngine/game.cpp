//Using SDL and standard IO
#include <list>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <xstring>

#include "StateMachine/EnemyTurnState.h"
#include "Global.h"
#include "StateMachine/PlayerTurnState.h"
#include "StateMachine/GameState.h"
#include "SubSystems/InputSystem.h"
#include "SubSystems/SubsystemCollection.h"
#include "RenderEngine/RenderEngine.h"

InputSystem* mInputSystem;
GameState *mCurrentGameState;
VisualElement* mVisualElements[2];
Uint32 mMsLast;

int Init();
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
		
		mCurrentGameState->Begin();
		mCurrentGameState->DoState();
		GameState* new_game_state = mCurrentGameState->Finish(mCurrentGameState);
		if(new_game_state != nullptr)
		{
			mCurrentGameState = new_game_state;
		}
		//Late. Might move order
		RenderEngine::PreRenderCheck();
		SUBSYSTEM_COLLECTION->IterateLateUpdate();
	// Tick
		const Uint32 ms_current = SDL_GetTicks();
		const Uint32 ms_delta = ms_current - mMsLast;
		mMsLast = ms_current;

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
/*TODO:Perhaps we can compress the updating while loop into it's own method as well. Could be used to pass global parameters/objects in for reverse dependency injection for example
*/
}

int Init()
{
	/*TODO: These came with the base project from Mark. They'd probably be more appropriate moved to global and written as global consts.
	*/
	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags))
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
	InitGlobals();
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
	
	mInputSystem = SUBSYSTEM_COLLECTION->GetSubSystem<InputSystem>();

	if (!mInputSystem)
	{
		printf("No InputSystem");
		return false;
	}
	RenderEngine::Init();
	mCurrentGameState = new GameState();
	mCurrentGameState->SetEnemyState(new EnemyTurnState());
	mCurrentGameState->SetPlayerState(new PlayerTurnState());
	mCurrentGameState->Begin();
	GameState* new_game_state = mCurrentGameState->Finish(mCurrentGameState);
	if(new_game_state != nullptr)
	{
		//printf("updating state");
		mCurrentGameState = new_game_state;
	}
	else
	{
		printf("null state");
	}
	return true;
}

void Close()
{
	RenderEngine::Quit();
	GPU_Quit();
	IMG_Quit();
	SDL_Quit();
}
