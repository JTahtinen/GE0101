#include "texturedata.h"
#include "../../defs.h"

TextureData::TextureData()
{
	_data.reserve(30);
}

void TextureData::loadTexture(const std::string& filepath)
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(filepath);
	addTexture(texture);
}

void TextureData::addTexture(std::shared_ptr<Texture> texture)
{
	if (!texture)
	{
		WARN("Could not push Texture to Texture Data - nullptr exception");
		return;
	}
	_data.push_back(texture);
}

TextureData::~TextureData()
{
	_data.clear();
}

void TextureData::removeTexture(const std::string& name)
{
	for (unsigned int i = 0; i < _data.size(); ++i)
	{
		if (_data[i]->getFilePath() == name)
		{
			_data.erase(_data.begin() + i);
			MSG("Deleted texture: " << name);
			return;
		}
	}
	WARN("Could not remove " << name << " - No such Texture in Texture Data");
}

std::shared_ptr<const Texture> TextureData::getTexture(const std::string& name) const
{
	for (auto& texture : _data)
	{
		if (texture->getFilePath() == name)
		{
			return texture;
		}
	}
	WARN("Could not retrieve Texture: " << name << " from Texture Data - no such texture");
	return nullptr;
}