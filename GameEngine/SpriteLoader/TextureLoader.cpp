#include "TextureLoader.h"

#include <filesystem>
#include <SDL_image.h>

Texture::Texture(GPU_Image* texture):image(texture){}

GPU_Image* Texture::GetImage()
{
    return image;
}

int Texture::GetWidth()
{
    return image->w;
}

int Texture::GetHeight()
{
    return image->h;
}

float Texture::GetWidthF()
{
    return static_cast<float>(GetWidth());
}

float Texture::GetHeightF()
{
    return static_cast<float>(GetHeight());
}


TextureLoader::TextureLoader()
{

}

TextureLoader::~TextureLoader()
{
    for (auto element: mTextureMap)
    {
        GPU_FreeImage(element.second->GetImage());
        delete element.second;
        delete element.first;
    }
    mTextureMap.clear();
}

Texture* TextureLoader::LoadTexture(const char* path)
{

    if(mTextureMap.contains(path))
    {
        return mTextureMap[path];
    }
    Texture* newTexture;
    printf(path);
    auto loadedImage = GPU_LoadImage(path);
    if (loadedImage == nullptr)
    {
        printf("Unable to load image %s! GPU_LoadImage Error.\n",path);
        return nullptr;
    }

    newTexture = new Texture(loadedImage);
    mTextureMap.insert({path,newTexture});
    return newTexture;
}
/*
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
*/
