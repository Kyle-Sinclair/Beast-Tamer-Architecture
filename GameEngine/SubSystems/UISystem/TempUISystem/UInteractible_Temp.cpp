#include "UInteractible_Temp.h"

#include "../UICommand.h"
#include "../../../Global.h"
#include "../../../RenderEngine/RenderEngine.h"

UInteractible_Temp::UInteractible_Temp(VisualElement* visualElement, GPU_Rect* interactibleRect, UICommand* boundCommand)
{
    this->visualElement = visualElement;
    this->interactibleRect = visualElement->GetRenderRect();
    interactCommand = boundCommand;
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
            char* charPointer{};
            interactCommand->Execute(charPointer);
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

    //TODO: Actually a ripe little test case for logging when we get around to it.
    //printf("%f,%f", (point.x - rect->x)/(float)rect->w,(point.y - rect->y)/((float)rect->h));
  
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
