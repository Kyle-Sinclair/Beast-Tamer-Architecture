//Using SDL and standard IO
#include <list>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <xstring>

#include "StateMachine/enemy_turn_state.h"
#include "Global.h"
#include "SpriteLoader/VisualElementFactory.h"
#include "StateMachine/PlayerTurnState.h"
#include "StateMachine/game_state.h"
#include "SubSystems/InputSystem.h"
#include "SubSystems/SubsystemCollection.h"
#include "RenderEngine/RenderEngine.h"

const char* pikachuImagePath{ "img/pikachu.png" };
const char* mouseImagePath{ "img/mouse_icon.png" };

//These variables store details about where the text object will be rendered.
//They should be moved to a struct that can be represented in an visual element object rather than stored as floating values in this class
//Currently they are being set in the LoadText method
int width;
int height;
int textWidth, textHeight;

//DEBUG MOUSE
SDL_Rect mouseRect {0, 0, 8, 8};

//These parameters describe the SDL_Rect properties for the pikachu image.
//They should be moved into a struct as part of a visual element bundle
//Currently they are being set in the load image method
SDL_Rect pikachuRect {0, 0, 16, 16};

SDL_Surface* textSurface;

int pikachuMoveX = 0;
int pikachuMoveY = 0;
SDL_Color textColor = { 0xff, 0xff, 0xff };

InputSystem* inputSystem;
game_state *CurrentGameState;
VisualElement* VisualElements[2];

Uint32 msLast;

bool Init();
bool InitGlobals();
void ProcessInput();
void Update(float deltaTime);
SDL_Texture* LoadText(const char* textToLoad);
SDL_Texture* LoadSprite(const char* imagePath);
void RenderSprite(SDL_Texture* sprite, SDL_Rect targetRectangle);
void RenderText(SDL_Texture* textToRender);
void ClearScreen();
void Close();

int main(int argc, char* args[])
{
	//Flag setting
	Init();

	//Update Loop
	while (gQuit == false)
	{
		//Early
		gSubsystemCollection->IterateEarlyUpdate();
		CurrentGameState->Begin();
		CurrentGameState->ProcessInput();
		CurrentGameState->DoState();
		game_state* NewGameState = CurrentGameState->Finish(CurrentGameState);
		if(NewGameState != nullptr)
		{
			CurrentGameState = NewGameState;
		}
		//Late. Might move order
		ProcessInput();
		RenderEngine::PreRenderCheck();

		gSubsystemCollection->IterateLateUpdate();
		
/*MVC
 *
View has no idea about hte data it's showing.
Model -> Business Logic
Model -> pushes to View shit to show

*/		// Tick
		const Uint32 msCurrent = SDL_GetTicks();
		const Uint32 msDelta = msCurrent - msLast;
		msLast = msCurrent;

		// Draw and present

		RenderEngine::Render();

		//todo lazy fps cap fix later plz
		SDL_Delay(1000/SCREEN_FPS); // can be used to wait for a certain amount of ms
	}

	// Destroying textures should be moved into texture management function.

	Close();
	
	return 0;
}

SDL_Texture* LoadSprite(const char* imagePath)
{
	SDL_Surface* loadedSurface = IMG_Load(imagePath);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", pikachuImagePath, IMG_GetError());
		return nullptr;
	}
	else
	{
		//Convert surface to screen format
		SDL_Texture* sprite_to_load = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (sprite_to_load == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", pikachuImagePath, SDL_GetError());
			return nullptr;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		return sprite_to_load;
	}
}

SDL_Texture* LoadText(const char* text_to_render)
{
	// load font
	auto font = TTF_OpenFont("font/lazy.ttf", 16);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return nullptr;
	}
	// render the text into an unoptimized CPU surface
	textSurface = TTF_RenderText_Solid(font, text_to_render, textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return nullptr;
	}
	else
	{
		// Create texture GPU-stored texture from surface pixels
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (textTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return nullptr;
		}
		// Get image dimensions
		width = textSurface->w;
		height = textSurface->h;
		textWidth = textSurface->w;
		textHeight = textSurface->h;
		//Get rid of old loaded surface
		SDL_FreeSurface(textSurface);
		
		return textTexture;
	}	
}

void RenderSprite(SDL_Texture* spriteToRender, SDL_Rect targetRectangle)
{
	SDL_RenderCopy(gRenderer, spriteToRender, NULL, &targetRectangle);
}

void RenderText(SDL_Texture* textTexture)
{
	SDL_Rect targetRectangle = SDL_Rect{
		INTERNAL_SCREEN_WIDTH/2 - textWidth/2,
		INTERNAL_SCREEN_HEIGHT/2 - textHeight/2,
		textWidth,
		textHeight
	};
	SDL_RenderCopy(gRenderer, textTexture, NULL, &targetRectangle);
}

void RenderText(SDL_Rect* targetRectangle, SDL_Texture* textTexture)
{
	SDL_RenderCopy(gRenderer, textTexture, NULL, targetRectangle);
}

void ProcessInput()
{
	
}

void Update(float deltaTime)
{

	
}

void ClearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 120, 60, 255, 255);
	SDL_RenderClear(gRenderer);
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
	
	//VisualElements[0] = visual_element_factory->CreateVisualElement(pikachuImagePath);
	//VisualElements[1] = visual_element_factory->CreateVisualElement("Resources/PokemonSprites/Minun.png",0,0,1,1,1,3,1);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");  // no smoothing pixel art.
	SDL_RenderSetLogicalSize(gRenderer, INTERNAL_SCREEN_WIDTH, INTERNAL_SCREEN_HEIGHT);
	
	printf("Initialising called\n");
	return true;
}

bool InitGlobals()
{
	gSubsystemCollection = new SubsystemCollection();

	if (!gSubsystemCollection)
	{
		printf("No SubsystemCollection");
		return false;
	}
	
	inputSystem = gSubsystemCollection->GetSubSystem<InputSystem>();

	if (!inputSystem)
	{
		printf("No InputSystem");
		return false;
	}
	RenderEngine::Init();
	CurrentGameState = new game_state();
	CurrentGameState->set_enemy_state(new enemy_turn_state());
	CurrentGameState->set_player_state(new player_turn_state());
	CurrentGameState->Begin();
	game_state* NewGameState = 	CurrentGameState->Finish(CurrentGameState);
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
	SDL_DestroyRenderer(gRenderer); gRenderer = nullptr;
	SDL_DestroyWindow(gWindow); gWindow = nullptr;
	
	RenderEngine::Quit();
	GPU_Quit();
	IMG_Quit();
	SDL_Quit();
}
