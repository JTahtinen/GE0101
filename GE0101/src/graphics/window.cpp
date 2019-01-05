#include "window.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
	: _width(width)
	, _height(height)
{
	if (_width < 100)
	{
		_width = 100;
	}
	if (_height < 100)
	{
		_height = 100;
	}

	if (_width > 2000)
	{
		_width = 2000;
	}
	if (_height > 2000)
	{
		_height = 2000;
	}

	_win = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		_width, 
		_height, 
		SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	SDL_DestroyWindow(_win);
}

void Window::update() const
{
	SDL_UpdateWindowSurface(_win);
}

void Window::applySurface(const Surface* surface)
{
	if (!surface)
	{
		std::cout << "Warning: Could not apply surface to window - surface was null!" << std::endl;
		return;
	}
	SDL_BlitScaled(surface->_image, NULL, SDL_GetWindowSurface(_win), NULL);
}

Surface Window::createDrawSurface()
{
	return Surface(_width, _height);
}