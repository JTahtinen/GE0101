#pragma once

class HeapTracker
{
	size_t					_totalAllocations{ 0 };
	size_t					_freedAllocations{ 0 };
public:
	inline void allocate(size_t size)			{ _totalAllocations += size; }
	inline void freeAllocation(size_t size)		{ _freedAllocations += size; }
	inline size_t getTotalAllocationsInBytes() const	{ return _totalAllocations; }
	inline size_t getFreedAllocationsInBytes() const	{ return _freedAllocations; }
	inline size_t getCurrentAllocationsInBytes() const { return _totalAllocations - _freedAllocations; }
	inline float getTotalAllocationsInKiloBytes() const { return (float)getTotalAllocationsInBytes() * 0.001f; }
	inline float getFreedAllocationsInKiloBytes() const { return (float)getFreedAllocationsInBytes() * 0.001f; }
	inline float getCurrentAllocationsInKiloBytes() const { return getTotalAllocationsInKiloBytes() - getFreedAllocationsInKiloBytes(); }
	inline float getTotalAllocationsInMegaBytes() const { return getTotalAllocationsInKiloBytes() * 0.001f; }
	inline float getFreedAllocationsInMegaBytes() const { return  getFreedAllocationsInKiloBytes() * 0.001f; }
	inline float getCurrentAllocationsInMegaBytes() const { return getTotalAllocationsInMegaBytes() - getFreedAllocationsInMegaBytes(); }
};