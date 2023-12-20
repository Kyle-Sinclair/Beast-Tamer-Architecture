#include "RectTransform.h"

RectTransform::RectTransform()
{
    position = {0,0};
    size = {1,1};
    originAnchorPoint = top_left;
    parent = nullptr;
}

RectTransform::RectTransform(Vector position, Vector size, AnchorPoint anchorPoint, RectTransform* parent)
{
    this->position = position;
    this->size = size;
    this->originAnchorPoint = anchorPoint;
    this->parent = parent;
}
