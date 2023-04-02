#include "stdafx.h"
#include "Renderer.h"

#include <iostream>

#include <sstream>
#include <iomanip>

template <typename T>
std::string IntToHex(T i)
{
    std::stringstream stream;
    stream << "0x"
        << std::setfill('0') << std::setw(sizeof(T) * 2)
        << std::hex << i;
    return stream.str();
}

// Debug Functions
void glClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::string errorValue = IntToHex<GLenum>(error);
        std::cout << "[OpenGL] Error at GLenum: '" << errorValue << "'" << std::endl;
        std::cout << "Assertion on function: " << function << ", file: " << file << ", line (" << line << ")" << std::endl;

        return false;
    }

    return true;
}

void GLFWErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

