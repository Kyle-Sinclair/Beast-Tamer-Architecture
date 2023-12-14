#pragma once
#include <SDL_gpu.h>

struct ImageQuad
{
    GPU_Image Image;
    GPU_Rect SrcRect;
    GPU_Rect DstRect;
};
