#pragma once
#include "texture.h"
#include "../math/vec2.h"

class Sprite
{
public:
	const Texture&			_texture;
	const Vec2				_dimensions;
	const std::string		_name;
	Sprite(const Texture& texture, float width, float height, const std::string& name);
};