#include "Shader.h"

#include <SDL_gpu.h>

#include "FColor.h"

Shader::Shader(const char* id, const char* vert, const char* frag) : name(id), success(true)
{
    v = GPU_LoadShader(GPU_VERTEX_SHADER, vert);
    if (!v)
    {
        success = false;
        printf("\033[0;31mSDL_GPU: Failed to load vertex shader (%s):\n%s\033[0m\n", vert, GPU_GetShaderMessage());
    }

    f = GPU_LoadShader(GPU_FRAGMENT_SHADER, frag);
    if (!f)
    {
        success = false;
        printf("\033[0;31mSDL_GPU: Failed to load fragment shader (%s):\n%s\033[0m\n", frag, GPU_GetShaderMessage());
    }

    p = GPU_LinkShaders(v, f);
    if (!p)
    {
        success = false;
        printf("\033[0;31mSDL_GPU: Failed to link shader programs (%s):\n%s\033[0m\n", id, GPU_GetShaderMessage());
    }

    block = GPU_LoadShaderBlock(p, "gpu_Vertex", "gpu_TexCoord", nullptr, "gpu_ModelViewProjectionMatrix");
    GPU_ActivateShaderProgram(p, &block);
}

void Shader::Unload()
{
    GPU_FreeShaderProgram(p);
}

const char* Shader::GetName()
{
    return name;
}

Uint32 Shader::GetProgram()
{
    return p;
}

bool Shader::DidCompile()
{
    return success;
}

const GPU_ShaderBlock& Shader::GetBlock()
{
    return block;
}

int Shader::GetVariable(const char* id) const
{
    if (uniformMap.contains(id))
    {
        return uniformMap[id];
    }
    
    // Location returns -1 if it is not part of the final shader, so it can be optimized out.
    const int location = GPU_GetUniformLocation(p, id);
    if (location >= 0)
    {
        uniformMap[id] = location;
    }
    return location;
}

#define ID_GUARD(id, out) const int out = GetVariable(id); if ((out) < 0) return;

void Shader::SetFloat(const char* id, const float value)
{
    ID_GUARD(id, location)
    GPU_SetUniformf(location, value);
}

void Shader::SetInteger(const char* id, const int value)
{
    ID_GUARD(id, location)
    GPU_SetUniformi(location, value);
}

void Shader::SetColor(const char* id, const FColor value)
{
    ID_GUARD(id, location) 
    float fColor[4] = {value.R, value.G, value.B, value.A};
    GPU_SetUniformfv(location, 4, 1, fColor);
}

void Shader::SetVec2(const char* id, const float x, const float y)
{
    ID_GUARD(id, location) 
    float vec[2] = {x, y};
    GPU_SetUniformfv(location, 2, 1, vec);
}

#undef ID_GUARD
