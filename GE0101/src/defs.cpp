#include "defs.h"

void* operator new(size_t size)
{
#ifdef _DEBUG
	g_heapTracker.allocate(size);
#endif
	return malloc(size);
}

void* operator new[](size_t size)
{
#ifdef _DEBUG
	MSG("Allocated array of " << size << " bytes");
	g_heapTracker.allocate(size);
#endif
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
#ifdef _DEBUG
	g_heapTracker.freeAllocation(size);
#endif
	free(memory);
}

void operator delete[](void* memory, size_t size)
{
#ifdef _DEBUG
	MSG("Deallocated array of " << size << " bytes");
	g_heapTracker.freeAllocation(size);
#endif
	free(memory);
}