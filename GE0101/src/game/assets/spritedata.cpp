#include "spritedata.h"
#include "../../defs.h"

SpriteData::SpriteData()
{
	_data.reserve(50);
}

SpriteData::~SpriteData()
{
	for (auto& sprite : _data)
	{
		delete sprite;
	}
	_data.clear();
}

void SpriteData::pushSprite(Sprite* sprite)
{
	for (auto& s : _data)
	{
		if (s->getName() == sprite->getName())
		{
			WARN("Could not add sprite: " << s->getName() << " to Sprite data - name collision, or sprite already present");
			return;
		}
	}
	_data.push_back(sprite);
}

void SpriteData::removeSprite(const std::string& name)
{
	unsigned int i = 0;
	for (auto& sprite : _data)
	{
		if (sprite->getName() == name)
		{
			_data.erase(_data.begin() + i);
			MSG("Deleted Sprite: " << name);
		}
		++i;
	}
	WARN("Could not delete Sprite: " << name << " from asset data - not found");
}

const Sprite* SpriteData::getSprite(const std::string& name) const
{
	for (auto& sprite : _data)
	{
		if (sprite->getName() == name)
		{
			return sprite;
		}
	}
	WARN("Could not get Sprite: " << name << " from asset data - not found");
	return nullptr;
}