#pragma once
#include "Vector.h"

enum AnchorPoint
{
    Center,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Top,
    Bottom,
    Left,
    Right
};
struct RectTransform
{
    RectTransform();
    Vector Position;
    //Vector EulerRotation;
    Vector Size;
    AnchorPoint originAnchorPoint;
    RectTransform* parent;
};
