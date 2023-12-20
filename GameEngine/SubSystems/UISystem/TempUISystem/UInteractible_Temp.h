#pragma once
#include "../../../SpriteLoader/VisualElement.h"

class UICommand;

class UInteractible_Temp
{
public:
    
    UInteractible_Temp(VisualElement* visualElement, GPU_Rect* interactibleRect = nullptr, UICommand* boundCommand = nullptr);
    void ProcessEvent(int x, int y);
    bool Contains(Vector point);
protected:
    GPU_Rect* interactibleRect;
    VisualElement* visualElement;
    bool mMouseInsideElement = false;
    
    UICommand* interactCommand{};
    virtual void OnHoverBegin();
    virtual void OnHoverEnd();
    virtual void OnPressed();
    virtual void OnReleased();
};
