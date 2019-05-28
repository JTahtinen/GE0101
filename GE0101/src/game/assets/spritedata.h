#pragma once
#include <vector>
#include <string>
#include "../../graphics/sprite.h"
class SpriteData
{
	std::vector<const Sprite*>		_data;
public:
	SpriteData();
	~SpriteData();
	void pushSprite(Sprite* sprite);
	void removeSprite(const std::string& name);
	const Sprite* getSprite(const std::string& name) const;
};