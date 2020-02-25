#include "sprite.h"
#include "../util/file.h"
#include "../application/assetmanager.h"
#include <sstream>

std::shared_ptr<Sprite> Sprite::loadSprite(const std::string& filepath, AssetManager& assets)
{
	std::string file = load_text_file(filepath);
	if (file == "")
	{
		ERR("Could not load Sprite: " << filepath);
		return nullptr;
	}
	std::istringstream ss(file);
	std::string line = "";

	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

	sprite->name = filepath;
	while (ss >> line)
	{
		if (line == "texture:")
		{
			ss >> line;
			std::shared_ptr<Texture> texture = assets.get<Texture>(line);
			if (!texture)
			{
				ERR("Could not load Sprite: " << filepath << " - Invalid texture!");
				return nullptr;
			}
			sprite->texture = texture;
			continue;
		}
		if (line == "size:")
		{
			ss >> line;
			float w = stof(line);
			ss >> line;
			float h = stof(line);
			sprite->size = Vec2(w, h);
			continue;
		}
	}
	return sprite;
}