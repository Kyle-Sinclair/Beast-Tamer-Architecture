#include "InputSystem.h"

#include <cstddef>
#include <SDL_events.h>

InputSystem::InputSystem()
{
    input_data = new Input_Data();
}

InputSystem::~InputSystem()
{
    input_data = NULL;
}

void InputSystem::UpdateInputs()
{
    SDL_Event e;
    
    // loop through all pending events from Windows (OS)
    while (SDL_PollEvent(&e))
    {
        int sdl_keycode = e.key.keysym.sym;
        switch (e.type)
        {
        case SDL_KEYDOWN: {
                if (sdl_keycode == SDLK_LEFT) {
                    input_data->move_x = -1;
                }
                else if(sdl_keycode == SDLK_RIGHT) {
                    input_data->move_x = 1;
                }

                if (sdl_keycode == SDLK_UP) {
                    input_data->move_y = 1;
                }
                else if(sdl_keycode == SDLK_DOWN) {
                    input_data->move_y = -1;
                }
				
        } break;
        case SDL_KEYUP: {
                if ((sdl_keycode == SDLK_LEFT && input_data->move_x < 0) || (sdl_keycode == SDLK_RIGHT && input_data->move_x > 0)) {
                    input_data->move_x = 0;
                }
                if ((sdl_keycode == SDLK_DOWN && input_data->move_y < 0) || (sdl_keycode == SDLK_UP && input_data->move_y > 0))
                {
                    input_data->move_y = 0;
                }
							
        } break;
        case SDL_MOUSEMOTION: {
                input_data->mouse_x = e.motion.x;
                input_data->mouse_y = e.motion.y;
        } break;
        case SDL_MOUSEBUTTONDOWN:
            {
                input_data->action = e.button.button & SDL_BUTTON_LMASK;
            } break;
        case SDL_MOUSEBUTTONUP:
            {
                input_data->action = !(e.button.button & SDL_BUTTON_LMASK);
            }
        }
    }
}
