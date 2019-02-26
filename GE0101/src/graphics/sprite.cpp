#include "sprite.h"
#include "../defs.h"

Sprite::Sprite(const Texture& texture, float width, float height, const std::string& name)
	: 
	_texture(texture)
	, _dimensions(width, height)
	, _name(name)
{
}