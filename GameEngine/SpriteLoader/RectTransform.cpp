#include "RectTransform.h"

RectTransform::RectTransform()
{
    position = {0,0};
    size = {1,1};
    originAnchorPoint = top_left;
    parent = nullptr;
}
