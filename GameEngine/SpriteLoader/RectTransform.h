#pragma once
#include "Vector.h"

struct RectTransform
{
    Vector Position;
    //Vector EulerRotation;
    Vector Size;
    RectTransform* parent;
};
