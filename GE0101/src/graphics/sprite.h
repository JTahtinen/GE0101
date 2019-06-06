#pragma once
#include "texture.h"
#include "mesh.h"
#include "../math/vec2.h"

struct Sprite
{
	std::shared_ptr<const Texture>	texture;
	Vec2							size;
	std::string						name;
};