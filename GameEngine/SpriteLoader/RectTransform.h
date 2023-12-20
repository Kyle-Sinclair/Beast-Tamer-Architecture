#pragma once
#include "Vector.h"

enum AnchorPoint
{
    center,
    top_left,
    top_right,
    bottom_left,
    bottom_right,
    top,
    bottom,
    left,
    right
};
struct RectTransform
{
    RectTransform();
    RectTransform(Vector position,Vector size, AnchorPoint anchorPoint, RectTransform* parent);
    Vector position;
    //Vector EulerRotation;
    Vector size;
    AnchorPoint originAnchorPoint;
    RectTransform* parent;
};
