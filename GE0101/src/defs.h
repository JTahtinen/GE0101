#pragma once
#include <iostream>
#include "globals.h"



#define MSG(expr) std::cout << expr << std::endl
#define ERR(expr) std::cout << "[ERROR] " << expr << std::endl;
#define WARN(expr) std::cout << "[WARNING] " << expr << std::endl;
#define LOGMSG(expr) gameLog.message(expr)
#define LOGERR(expr) gameLog.error(expr)
#define LOGWARN(expr) gameLog.warning(expr)

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL ERROR] (" << error << ")" << std::endl;
		return false;
	}
	return true;
}

#ifdef  _DEBUG
#define ASSERT(expr) if (expr) {} else { __debugbreak(); }
#define GLCALL(expr) GLClearError();\
expr;\
ASSERT(GLLogCall())

#else

#define ASSERT(expr)
#define GLCALL(expr) expr

#endif