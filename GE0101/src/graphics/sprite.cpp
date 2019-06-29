#include "sprite.h"
#include "../util/file.h"
#include "../application/assetmanager.h"
#include <sstream>

std::shared_ptr<Sprite> Sprite::loadSprite(const std::string& filepath, AssetManager& assets)
{
	AssetCollection<Texture>& texData = assets.getData<Texture>();
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
			std::shared_ptr<Texture> texture = texData.getElement(line);
			if (!texture)
			{
				ERR("Could not load Sprite: " << filepath << " - Invalid texture!");
				MSG("Attempting to load texture: " << line);
				texture = assets.load<Texture>(line);
				if (!texture)
				{
					ERR("Failed!");
					return nullptr;
				}
				MSG("Success!");
			}
			sprite->texture = texData.getElement(line);
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