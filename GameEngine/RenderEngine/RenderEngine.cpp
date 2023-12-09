#include "RenderEngine.h"

#include <cstdio>
#include <SDL.h>
#include <GL/glew.h>

#include "../Global.h"

bool RenderEngine::Init()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    gWindow = SDL_CreateWindow("Design Pattern Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    gContext = SDL_GL_CreateContext(gWindow);
    if (!gContext)
    {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    }

    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }
    
    if (!InitGL())
    {
        printf("Unable to initialize OpenGL!\n");
        return false;
    }

    return true;
}

bool RenderEngine::InitGL()
{
    ProgramID = glCreateProgram();

    // Init Vertex shader
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Get vertex source
    const GLchar* vertexShaderSource[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };

    glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);

    glCompileShader(vertexShader);

    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE)
    {
        printf("Unable to compile vertex shader %d!\n", vertexShader);
        PrintShaderLog(vertexShader);
        return false;
    }

    glAttachShader(ProgramID, vertexShader);

    // Init Fragment shader
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* fragmentShaderSource[] =
    {
        "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
    };

    glShaderSource(fragmentShader, 1, fragmentShaderSource, nullptr);
    
    glCompileShader(fragmentShader);
    
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
    if (fShaderCompiled != GL_TRUE)
    {
        printf("Unable to compile fragment shader %d!\n", fragmentShader);
        PrintShaderLog(fragmentShader);
        return false;
    }

    glAttachShader(ProgramID, fragmentShader);

    // Init link
    glLinkProgram(ProgramID);
    
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE)
    {
        printf("Error linking program %d!\n", ProgramID);
        PrintProgramLog(ProgramID);
        return false;
    }

    VertexPos2DLocation = glGetAttribLocation(ProgramID, "LVertexPos2D");
    if (VertexPos2DLocation == -1)
    {
        printf("LVertexPos2D is not a valid glsl program variable!\n");
        return false;
    }
    
    glClearColor(0.f, 0.f, 0.f, 1.f);

    const GLfloat vertexData[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    const GLuint indexData[] = {0, 1, 2, 3};
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

    return true;
}

void RenderEngine::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind program
    glUseProgram(ProgramID);

    // Enable vertex position
    glEnableVertexAttribArray(VertexPos2DLocation);

    // Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(VertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

    // Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

    // Disable vertex position
    glDisableVertexAttribArray(VertexPos2DLocation);

    // Unbind program
    glUseProgram(NULL);
}

void RenderEngine::Quit()
{
}

void RenderEngine::PrintProgramLog(GLuint program)
{
    if (!glIsProgram(program))
    {
        printf("Name %d is not a program\n", program);
        return;
    }

    // Allocate string
    int infoLogLength = 0;
    int maxLength = infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    char* infoLog = new char[maxLength];

    // Get log
    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
        printf("%s\n", infoLog);
    }
    
    // Deallocate string
    delete[] infoLog;
}

void RenderEngine::PrintShaderLog(GLuint shader)
{
    if (!glIsShader(shader))
    {
        printf("Name %d is not a shader\n", shader);
        return;
    }
    
    // Allocate string
    int infoLogLength = 0;
    int maxLength = infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    char* infoLog = new char[maxLength];
        
    // Get log
    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
        printf("%s\n", infoLog);
    }

    // Deallocate string
    delete[] infoLog;
}
