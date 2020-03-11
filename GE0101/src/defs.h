#pragma once
#include <iostream>
#include "globals.h"
#include <GLEW/glew.h>


extern void* operator new(size_t size);
extern void* operator new[](size_t size);
extern void operator delete(void* memory, size_t size);
extern void operator delete[](void* memory, size_t size);

template<typename T> using ptr = std::shared_ptr<T>;
template<typename T> using ptr_s = std::shared_ptr<T>;
template<typename T> using ptr_u = std::unique_ptr<T>;
template<typename T> using ptr_w = std::weak_ptr<T>;

#ifdef _DEBUG
#define MSG(expr) std::cout << expr << std::endl
#define ERR(expr) std::cout << "[ERROR] " << expr << std::endl;
#define WARN(expr) std::cout << "[WARNING] " << expr << std::endl;
#else
#define MSG(expr)
#define ERR(expr)
#define WARN(expr)
#endif 

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