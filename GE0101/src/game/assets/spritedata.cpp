//#include "spritedata.h"
//#include "../../defs.h"
//#include "../../util/file.h"
//#include <sstream>
//
//SpriteData::SpriteData()
//{
//	_data.reserve(50);
//}
//
//SpriteData::~SpriteData()
//{
//	_data.clear();
//}
//
//void SpriteData::addSprite(std::shared_ptr<Sprite> sprite)
//{
//	for (const auto& s : _data)
//	{
//		if (s->name == sprite->name)
//		{
//			WARN("Could not add sprite: " << s->name << " to Sprite data - name collision, or sprite already present");
//			return;
//		}
//	}
//	_data.push_back(sprite);
//}
//
//void SpriteData::removeSprite(const std::string& name)
//{
//	unsigned int i = 0;
//	for (auto& sprite : _data)
//	{
//		if (sprite->name == name)
//		{
//			_data.erase(_data.begin() + i);
//			MSG("Deleted Sprite: " << name);
//		}
//		++i;
//	}
//	WARN("Could not delete Sprite: " << name << " from asset data - not found");
//}
//
//std::shared_ptr<const Sprite> SpriteData::getSprite(const std::string& name) const
//{
//	for (auto& sprite : _data)
//	{
//		if (sprite->name == name)
//		{
//			return sprite;
//		}
//	}
//	WARN("Could not get Sprite: " << name << " from asset data - not found");
//	return nullptr;
//}
//
//std::shared_ptr<Sprite> SpriteData::loadSprite(const std::string& filepath, TextureData& texData)
//{
//	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();
//	std::string file = load_text_file(filepath);
//	std::istringstream ss(file);
//	std::string line = "";
//
//	while (ss >> line)
//	{
//		if (line == "texture:")
//		{
//			ss >> line;
//			sprite->name = line;
//			sprite->texture = texData.getTexture(line);
//			continue;
//		}
//		if (line == "size:")
//		{
//			ss >> line;
//			float w = stof(line);
//			ss >> line;
//			float h = stof(line);
//			sprite->size = Vec2(w, h);
//			continue;
//		}
//	}
//	addSprite(sprite);
//	return sprite;
//}