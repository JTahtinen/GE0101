#pragma once
#include <SDL2\SDL.h>

class Surface 
{
	friend class Window;
	int						_width;
	int						_height;
public:
	SDL_Surface*			_image;
	unsigned int* const		_pixels;
public:
	Surface(int width, int height);
	~Surface();
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
	void clear();
	void fill(unsigned int color);
};