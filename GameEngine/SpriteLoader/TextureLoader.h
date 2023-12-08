#pragma once
#include <SDL_render.h>
#include <vector>
#include <map>


struct Texture
{
private:
    SDL_Texture* texture;
    int width;
    int height;
public:
    Texture(SDL_Texture* texture, int width,int height);
    SDL_Texture* GetTexture();
    int GetHeight();
    int GetWidth();
};

class TextureLoader
{
    private:
    std::map<const char*, Texture*> TextureMap;
    SDL_Renderer* renderer;
    
    public:
    TextureLoader(SDL_Renderer* renderer);
    ~TextureLoader();
    SDL_Surface* LoadSurface(const char* path);
    Texture* LoadTexture(const char* path);
};
