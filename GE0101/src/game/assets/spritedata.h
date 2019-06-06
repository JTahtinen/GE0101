#pragma once
#include <vector>
#include <string>
#include "../../graphics/sprite.h"
class SpriteData
{
	std::vector<std::shared_ptr<Sprite>>		_data;
public:
	SpriteData();
	~SpriteData();
	void addSprite(std::shared_ptr<Sprite> sprite);
	void removeSprite(const std::string& name);
	std::shared_ptr<const Sprite> getSprite(const std::string& name) const;
};