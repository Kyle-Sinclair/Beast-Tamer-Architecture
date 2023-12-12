#include "RectTransform.h"

RectTransform::RectTransform()
{
    Position = {0,0};
    Size = {1,1};
    originAnchorPoint = TopLeft;
    parent = nullptr;
}
