#pragma once

#include <GLEW/glew.h>

#ifdef _DEBUG

#define GL_ASSERT(x) if(!(x)) __debugbreak();
#define GL_CALL(function) glClearError(); \
						  function;\
						  GL_ASSERT(glLogCall(#function, __FILE__, __LINE__));


#else

#define GL_ASSERT(x) x;
#define GL_CALL(function) function;

#endif

void glClearError();
bool glLogCall(const char* function, const char* file, int line);

void GLFWErrorCallback(int error, const char* description);

namespace Autumn
{
	namespace Graphics
	{
		class Renderer
		{
		public:

		};
	}
}
