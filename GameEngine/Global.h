﻿#pragma once

//Contains global data about the game, some could be moved later but should be here for testing

//initial window res
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int SCREEN_FPS = 60;

//The internal resolution. Currently gba resolution
const int INTERNAL_SCREEN_WIDTH = 240;
const int INTERNAL_SCREEN_HEIGHT = 160;

extern class SubsystemCollection* gSubsystemCollection;

extern struct SDL_Window* gWindow;

extern struct SDL_Renderer* gRenderer;

extern bool gQuit;