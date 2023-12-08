#pragma once

#include <GL/glew.h>

class RenderEngine
{
public:
    static bool Init();
    
    static void Render();

    inline static GLuint ProgramID = 0;
    inline static GLint VertexPos2DLocation = -1;
    inline static GLuint VBO = 0;
    inline static GLuint IBO = 0;

private:
    static bool InitGL();

    static void PrintProgramLog(GLuint program);
    static void PrintShaderLog(GLuint shader);
};
