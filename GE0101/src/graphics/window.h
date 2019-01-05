#pragma once
#include <SDL2\SDL.h>
#include "surface.h"

class Window
{
	SDL_Window*		_win;
	int				_width;
	int				_height;
public:
	Window(int width, int height, const char* title);
	~Window();
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
	void update() const;
	void applySurface(const Surface* surface);

	Surface createDrawSurface();
};