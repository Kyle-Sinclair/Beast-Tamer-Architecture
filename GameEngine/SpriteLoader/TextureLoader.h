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
    Texture* LoadTexture(const char* path); 
    //SDL_Surface* LoadSurface(const char* path);
    //Texture* LoadTexture(const char* path);
};
