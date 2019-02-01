#pragma once
#include <iostream>
#include "globals.h"

#ifdef _DEBUG
#define ASSERT(expr) if(expr) { } else { __debugbreak(); }
#else
#define ASSERT(x) 
#endif

#define MSG(expr) std::cout << expr << std::endl
#define ERR(expr) std::cout << "[ERROR] " << expr << std::endl;
#define WARN(expr) std::cout << "[WARNING] " << expr << std::endl;
#define LOGMSG(expr) gameLog.message(expr)
#define LOGERR(expr) gameLog.error(expr)
#define LOGWARN(expr) gameLog.warning(expr)