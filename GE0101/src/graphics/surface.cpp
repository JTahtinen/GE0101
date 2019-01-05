#include "surface.h"
#include "../defs.h"

Surface::Surface(int width, int height)
	: _width(width)
	, _height(height)
	, _image(SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0))
	, _pixels((unsigned int* const)_image->pixels)
{
	ASSERT(_image);

	clear();
}

Surface::~Surface()
{
	SDL_FreeSurface(_image);
	_image = nullptr;
}

void Surface::clear()
{
	for (int i = 0; i < _width * _height; ++i)
	{
		_pixels[i] = 0;
	}
}