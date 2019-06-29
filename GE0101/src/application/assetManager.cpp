#include "assetmanager.h"

#define ASSET_OPERATIONS()


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
	return font;
}

template<>
std::shared_ptr<Texture> AssetManager::load<Texture>(const std::string& filepath)
{
	std::shared_ptr<Texture> texture = Texture::loadTexture(filepath);
	if (texture)
	{
		_textureData.addElement(texture, filepath);
	}
	return texture;
}

template<>
std::shared_ptr<Sprite> AssetManager::load<Sprite>(const std::string& filepath)
{
	std::shared_ptr<Sprite> sprite = Sprite::loadSprite(filepath, *this);
	if (sprite)
	{
		_spriteData.addElement(sprite, filepath);
	}
	return sprite;
}

template<>
void AssetManager::add<Font>(std::shared_ptr<Font> element, const std::string& name)
{
	_fonts.emplace(name, element);
}

template<>
void AssetManager::add<Texture>(std::shared_ptr<Texture> element, const std::string& name)
{
	_textures.emplace(name, element);
}

template<>
void AssetManager::add<Sprite>(std::shared_ptr<Sprite> element, const std::string& name)
{
	_sprites.emplace(name, element);
}

template<>
void AssetManager::remove<Font>(const std::string& name)
{
	_fonts.erase(name);
}

void removeElement<Texture>(const std::string& name)
{
	_data.erase(name);
}

void removeElement(const std::string& name)
{
	_data.erase(name);
}
std::shared_ptr<T> getElement(const std::string& name)
{
	std::shared_ptr<T> elem = _data[name];
	if (!elem)
	{
		ERR("AssetManager: Could not get asset: " << name);
		return nullptr;
	}
	return elem;
}