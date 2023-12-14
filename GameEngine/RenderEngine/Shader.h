#pragma once

#include <SDL.h>
#include <SDL_gpu.h>
#include <unordered_map>

struct FColor;

class Shader
{
public:
    Shader(const char* id, const char* vert, const char* frag);

    void Unload();
    
    const char* GetName();

    Uint32 GetProgram();

    bool DidCompile();

    const GPU_ShaderBlock& GetBlock();
    
    int GetVariable(const char* id) const;

    void SetFloat(const char* id, float value);
    
    void SetInteger(const char* id, int value);
    
    void SetColor(const char* id, FColor value);
    
    void SetVec2(const char* id, float x, float y);
    
private:
    const char* name;

    bool success;

    mutable std::pmr::unordered_map<const char*, int> uniformMap;
    
    // Vertex shader, fragment shader and linked program
    Uint32 v, f, p;

    GPU_ShaderBlock block;
};
