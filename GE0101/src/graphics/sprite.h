#pragma once
#include "texture.h"
#include "mesh.h"
#include "../math/vec2.h"

class AssetManager; 

class Sprite
{
public:
	std::shared_ptr<const Texture>	texture;
	Vec2							size;
	std::string						name;

	static std::shared_ptr<Sprite> loadSprite(const std::string& filepath, AssetManager& assets);
};