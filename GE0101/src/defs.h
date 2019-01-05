#pragma once

#ifdef _DEBUG
#define ASSERT(x) if(x) { } else { __debugbreak(); }
#else
#define ASSERT(x) 
#endif