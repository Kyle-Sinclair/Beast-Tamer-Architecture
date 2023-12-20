#include "UInteractible_Temp.h"

#include "../../../Global.h"
#include "../../../RenderEngine/RenderEngine.h"

UInteractible_Temp::UInteractible_Temp(VisualElement* visualElement, GPU_Rect* interactibleRect)
{
    this->visualElement = visualElement;
    this->interactibleRect = visualElement->GetRenderRect();
   // this->interactibleRect->x -= visualElement->GetTransform()->position.x;
   // this->interactibleRect->y -= visualElement->GetTransform()->position.y;
   /// this->interactibleRect = interactibleRect;
}

void UInteractible_Temp::ProcessEvent(int x, int y)
{
    
        Vector mousePosition;
        
    
        x -= RenderEngine::screenRect->x;
        x = INTERNAL_SCREEN_WIDTH * x/ RenderEngine::screenRect->w;
        y -= RenderEngine::screenRect->y;
        y = INTERNAL_SCREEN_HEIGHT * y / RenderEngine::screenRect->h;
    
        printf("MousePosition (%d,%d)",x,y);
        mousePosition.x = x;
        mousePosition.y = y;
        if(Contains(mousePosition))
        {
            printf("You clicked!");
        }
        /*
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
        */
    
}

bool UInteractible_Temp::Contains(Vector point)
{
    const GPU_Rect* rect = (interactibleRect == nullptr)? visualElement->GetRenderRect(): interactibleRect;

    printf("%f,%f", (point.x - rect->x)/(float)rect->w,(point.y - rect->y)/((float)rect->h));
    //printf("%f,%f", rect->x + rect->w, rect->y + rect->h);

    //printf("%f,%f", rect->x + rect->w, rect->y + rect->h);
    //printf("%f,%f\n", rect->x - rect->w, rect->y - rect->h);
    const bool lessThanX =  point.x < rect->x + rect->w;
    const bool greaterThanX =  point.x >= rect->x;
    const bool lessThanY = point.y < rect->y + rect->h;
    const bool greaterThanY = point.y >= rect->y;

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
