#include "TextureLoader.h"

#include <filesystem>
#include <SDL_image.h>

Texture::Texture(SDL_Texture* texture, int width, int height)
{
    this->texture = texture;
    this->width = width;
    this->height = height;
}

SDL_Texture* Texture::GetTexture()
{
    return texture;
}

int Texture::GetHeight()
{
    return height;
}

int Texture::GetWidth()
{
    return width;
}

TextureLoader::TextureLoader(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

TextureLoader::~TextureLoader()
{
    renderer = nullptr;
    for (auto element: TextureMap)
    {
        delete element.second;
        delete element.first;
    }
    TextureMap.clear();
}

SDL_Surface* TextureLoader::LoadSurface(const char* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return nullptr;
    }
    return loadedSurface;
}


Texture* TextureLoader::LoadTexture(const char* path)
{
    if(TextureMap.contains(path))
    {
        return TextureMap[path];
    }
    
    SDL_Surface* loadedSurface = LoadSurface(path);
    //Convert surface to screen format
    SDL_Texture* sprite_to_load = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (sprite_to_load == nullptr)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        return nullptr;
    }
    
    const auto sprite = new Texture(sprite_to_load, loadedSurface->w,loadedSurface->h);
    TextureMap.insert({path,sprite});
    
    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
    return sprite;
}
