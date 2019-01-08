#include "surface.h"
#include "../defs.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Surface::Surface(int width, int height)
	: _width(width)
	, _height(height)
	, _image(SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0))
	, _pixels((unsigned int* const)_image->pixels)
{
	ASSERT(_image);
	fill(0xff0000);
	//clear();
}

Surface::Surface(SDL_Surface* source)
	: _width(source->w)
	, _height(source->h)
	, _image(source)
	, _pixels((unsigned int*)source->pixels)
{
	ASSERT(_image);
}

Surface::~Surface()
{
	SDL_FreeSurface(_image);
	_image = nullptr;
}

void Surface::fill(unsigned int color)
{
	for (int i = 0; i < _width * _height; ++i)
	{
		_pixels[i] = color;
	}
}

void Surface::clear()
{
	fill(0);
}

Surface* Surface::loadSurface(const char* filepath)
{
	SDL_Surface* rawSurface = IMG_Load(filepath);
	if (!rawSurface)
	{
		std::cout << "WARNING: Could not load image: " << filepath << std::endl;
		return nullptr;
	}
	return convertToSurface(rawSurface);
}

Surface* Surface::convertToSurface(SDL_Surface* surface)
{
	if (!surface)
	{
		std::cout << "WARNING: Conversion failed - Surface was NULL" << std::endl;
		return nullptr;
	}
	return new Surface(surface);
}