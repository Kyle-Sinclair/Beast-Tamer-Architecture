#include "UInteractible_Temp.h"

#include "../../../Global.h"

UInteractible_Temp::UInteractible_Temp(VisualElement* visualElement, GPU_Rect* interactibleRect)
{
    this->visualElement = visualElement;
    this->interactibleRect = interactibleRect;
}

void UInteractible_Temp::ProcessEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP|| e->type == SDL_MOUSEMOTION)
    {
        Vector mousePosition;
        int x;
        int y;
        SDL_GetMouseState(&x,&y);
        x *= (float)INTERNAL_SCREEN_WIDTH/SCREEN_WIDTH;
        y *= (float)INTERNAL_SCREEN_HEIGHT/SCREEN_HEIGHT;
        //printf("MousePosition (%d,%d)",x,y);
        mousePosition.x = x;
        mousePosition.y = y;
        
        if(e->type == SDL_MOUSEMOTION)
        {
            if(Contains(mousePosition) && !mMouseInsideElement)
            {
                OnHoverBegin();
                mMouseInsideElement = true;
            }
            else if(!Contains(mousePosition) && mMouseInsideElement)
            {
                OnHoverEnd();
                mMouseInsideElement = false;
            }
        }

        if(e->type == SDL_MOUSEBUTTONDOWN && Contains(mousePosition))
        {
            OnPressed();
        }
        if(e->type == SDL_MOUSEBUTTONUP && Contains(mousePosition))
        {
            OnReleased();
        }
    }
}

bool UInteractible_Temp::Contains(Vector point)
{
    const GPU_Rect* rect = (interactibleRect == nullptr)? visualElement->GetRenderRect(): interactibleRect;

    const bool lessThanX =  point.x < rect->x + rect->w;
    const bool greaterThanX =  point.x > rect->x - rect->w;
    const bool lessThanY = point.y < rect->y + rect->h;
    const bool greaterThanY = point.y > rect->y - rect->h;

    return lessThanX && greaterThanX && lessThanY && greaterThanY;
}

void UInteractible_Temp::OnHoverBegin()
{
    printf("OnHoverBegin");
}

void UInteractible_Temp::OnHoverEnd()
{
    printf("OnHoverEnd");
}

void UInteractible_Temp::OnPressed()
{
    printf("OnHoverPressed");
}

void UInteractible_Temp::OnReleased()
{
    printf("OnHoverReleased");
}
