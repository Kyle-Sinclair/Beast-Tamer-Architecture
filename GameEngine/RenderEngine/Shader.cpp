#include "Shader.h"

#include <SDL_gpu.h>

#include "FColor.h"

Shader::Shader(const char* id, const char* vert, const char* frag) : mName(id), mSuccess(true)
{
    mV = GPU_LoadShader(GPU_VERTEX_SHADER, vert);
    if (!mV)
    {
        mSuccess = false;
        printf("\033[0;31mSDL_GPU: Failed to load vertex shader (%s):\n%s\033[0m\n", vert, GPU_GetShaderMessage());
    }

    mF = GPU_LoadShader(GPU_FRAGMENT_SHADER, frag);
    if (!mF)
    {
        mSuccess = false;
        printf("\033[0;31mSDL_GPU: Failed to load fragment shader (%s):\n%s\033[0m\n", frag, GPU_GetShaderMessage());
    }

    mP = GPU_LinkShaders(mV, mF);
    if (!mP)
    {
        mSuccess = false;
        printf("\033[0;31mSDL_GPU: Failed to link shader programs (%s):\n%s\033[0m\n", id, GPU_GetShaderMessage());
    }

    mBlock = GPU_LoadShaderBlock(mP, "gpu_Vertex", "gpu_TexCoord", nullptr, "gpu_ModelViewProjectionMatrix");
    GPU_ActivateShaderProgram(mP, &mBlock);
}

void Shader::Unload()
{
    GPU_FreeShaderProgram(mP);
}

const char* Shader::GetName()
{
    return mName;
}

Uint32 Shader::GetProgram()
{
    return mP;
}

bool Shader::DidCompile()
{
    return mSuccess;
}

const GPU_ShaderBlock& Shader::GetBlock()
{
    return mBlock;
}

int Shader::GetVariable(const char* id) const
{
    if (mUniformMap.contains(id))
    {
        return mUniformMap[id];
    }
    
    // Location returns -1 if it is not part of the final shader, so it can be optimized out.
    const int location = GPU_GetUniformLocation(mP, id);
    if (location >= 0)
    {
        mUniformMap[id] = location;
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
    float fColor[4] = {value.r, value.g, value.b, value.a};
    GPU_SetUniformfv(location, 4, 1, fColor);
}

void Shader::SetVec2(const char* id, const float x, const float y)
{
    ID_GUARD(id, location) 
    float vec[2] = {x, y};
    GPU_SetUniformfv(location, 2, 1, vec);
}

#undef ID_GUARD
