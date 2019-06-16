#include "assetmanager.h"

template<>
AssetCollection<Font>& AssetManager::getData<Font>()
{
	return _fontData;
}

template<>
AssetCollection<Texture>& AssetManager::getData<Texture>()
{
	return _textureData;
}

template<>
AssetCollection<Sprite>& AssetManager::getData<Sprite>()
{
	return _spriteData;
}

template<>
std::shared_ptr<Font> AssetManager::load<Font>(const std::string& filepath)
{
	std::shared_ptr<Font> font = Font::loadFont(filepath);
	if (font)
	{
		_fontData.addElement(font, filepath);
	}
}

template<>
std::shared_ptr<Texture> AssetManager::load<Texture>(const std::string& filepath)
{
	std::shared_ptr<Texture> texture = Texture::loadTexture(filepath);
	if (texture)
	{
		_textureData.addElement(texture, filepath);
	}
}

template<>
std::shared_ptr<Sprite> AssetManager::load<Sprite>(const std::string& filepath)
{
	std::shared_ptr<Sprite> sprite = Sprite::loadSprite(filepath, *this);
	if (sprite)
	{
		_spriteData.addElement(sprite, filepath);
	}
}