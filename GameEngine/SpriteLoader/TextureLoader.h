#pragma once
#include <SDL_render.h>
#include <vector>
#include <map>
#include <SDL_gpu.h>


struct Texture
{
private:
    GPU_Image* image;
public:
    Texture(GPU_Image* texture);
    GPU_Image* GetImage();
    int GetWidth();
    int GetHeight();
    float GetWidthF();
    float GetHeightF();
};

class TextureLoader
{
    private:
    std::map<const char*, Texture*> mTextureMap;
    
    public:
    TextureLoader();
    ~TextureLoader();
    //TODO: Most of our path sharing currently use const char pointers. Given what we want to do with data driven stuff, moving to a more flexible string class is probably better
    Texture* LoadTexture(const char* path); 
    //SDL_Surface* LoadSurface(const char* path);
    //Texture* LoadTexture(const char* path);
};
