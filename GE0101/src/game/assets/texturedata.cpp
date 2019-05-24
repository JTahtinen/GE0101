#include "texturedata.h"
#include "../../defs.h"

TextureData::TextureData()
{
	_data.reserve(30);
}

void TextureData::loadTexture(const std::string& filepath)
{
	Texture* texture = new Texture(filepath);
	pushTexture(texture);
}

void TextureData::pushTexture(Texture* texture)
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
	for (auto& texture : _data)
	{
		delete texture;
	}
	_data.clear();
}

void TextureData::popTexture(const std::string& name)
{
	for (unsigned int i = 0; i < _data.size(); ++i)
	{
		if (_data[i]->getFilePath() == name)
		{
			delete _data[i];
			_data[i] = nullptr;
			MSG("Deleted texture: " << name);
			return;
		}
	}
	WARN("Could not pop " << name << " - No such Texture in Texture Data");
}

const Texture* TextureData::getTexture(const std::string& name) const
{
	for (auto& texture : _data)
	{
		if (texture->getFilePath() == name)
		{
			return texture;
		}
	}
	WARN("Could not get Texture " << name << " from Texture Data - no such texture");
	return nullptr;
}