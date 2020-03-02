#pragma once
#include <chrono>
#include <time.h>

class Timer
{
	std::chrono::steady_clock::time_point			_startTime;
	std::chrono::steady_clock::time_point			_currentTime;
	std::chrono::steady_clock::time_point			_lastTime;
public:
	inline void start()
	{
		_startTime = std::chrono::high_resolution_clock::now();
		_currentTime = _startTime;
		_lastTime = _startTime;
	}
	unsigned int getElapsedInMillis() const
	{
		return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(_currentTime - _startTime).count();
	}
	inline unsigned int getElapsedSinceLastUpdateInMillis() const
	{
		return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(_currentTime - _lastTime).count();
	}
	inline void update()
	{
		_lastTime = _currentTime;
		_currentTime = std::chrono::high_resolution_clock::now();
	}
};