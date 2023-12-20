#pragma once
#include "../../../SpriteLoader/VisualElement.h"

class UInteractible_Temp
{
public:
    
    UInteractible_Temp(VisualElement* visualElement, GPU_Rect* interactibleRect = nullptr);
    void ProcessEvent(SDL_Event* e);
    bool Contains(Vector point);
protected:
    GPU_Rect* interactibleRect;
    VisualElement* visualElement;
    bool mMouseInsideElement = false;
    virtual void OnHoverBegin();
    virtual void OnHoverEnd();
    virtual void OnPressed();
    virtual void OnReleased();
};
