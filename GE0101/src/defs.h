#pragma once
#include <iostream>

#ifdef _DEBUG
#define ASSERT(expr) if(expr) { } else { __debugbreak(); }
#else
#define ASSERT(x) 
#endif

#define MSG(expr) std::cout << expr << std::endl