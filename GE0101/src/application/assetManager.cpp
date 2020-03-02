#include "assetmanager.h"

AssetManager::~AssetManager()
{
	_fontData.clear();
	message("Fonts cleared");
	_textureData.clear();
	message("Textures cleared");
	_spriteData.clear();
	message("Sprites cleared");
}

template<>
std::shared_ptr<Font> AssetManager::load<Font>(const std::string& filepath)
{
	std::shared_ptr<Font> font = Font::loadFont(filepath);
	if (font)
	{
		_fontData.addElement(font, filepath);
		message("Font: " + filepath + " loaded succesfully");
		return font;
	}
	error("Could not load Font: " + filepath);
	return nullptr;
}

template<>
std::shared_ptr<Texture> AssetManager::load<Texture>(const std::string& filepath)
{
	std::shared_ptr<Texture> texture = Texture::loadTexture(filepath);
	if (texture)
	{
		_textureData.addElement(texture, filepath);
		message("Texture: " + filepath + " loaded succesfully");
		return texture;
	}
	error("Could not load Texture: " + filepath);
	return nullptr;
}

template<>
std::shared_ptr<Sprite> AssetManager::load<Sprite>(const std::string& filepath)
{
	std::shared_ptr<Sprite> sprite = Sprite::loadSprite(filepath, *this);
	if (sprite)
	{
		_spriteData.addElement(sprite, filepath);
		message("Sprite: " + filepath + " loaded succesfully");
		return sprite;
	}
	error("Could not load Sprite: " + filepath);
	return nullptr;
}

template<>
void AssetManager::add<Font>(std::shared_ptr<Font> element, const std::string& name)
{
	if (_fontData.getElement(name) == nullptr)
	{
		error("Font " + name + "already loaded");
		return;
	}
	_fontData.addElement(element, name);
}

template<>
void AssetManager::add<Texture>(std::shared_ptr<Texture> element, const std::string& name)
{
	_textureData.addElement(element, name);
}

template<>
void AssetManager::add<Sprite>(std::shared_ptr<Sprite> element, const std::string& name)
{
	_spriteData.addElement(element, name);
}

template<>
void AssetManager::remove<Font>(const std::string& name)
{
	_fontData.removeElement(name);
}

template<>
void AssetManager::remove<Texture>(const std::string& name)
{
	_textureData.removeElement(name);
}

template<>
std::shared_ptr<Texture> AssetManager::get<Texture>(const std::string& name)
{
	std::shared_ptr<Texture> texture = _textureData.getElement(name);
	if (!texture)
	{
		message("Could not get Texture: " + name + ". Attempting to load Texture from file.");
		texture = load<Texture>(name);
	}
	return texture;
}

template<>
std::shared_ptr<Sprite> AssetManager::get<Sprite>(const std::string& name)
{
	std::shared_ptr<Sprite> sprite = _spriteData.getElement(name);
	if (!sprite)
	{
		message("Could not get Sprite: "  + name + ". Attempting to load Sprite from file.");
		sprite = load<Sprite>(name);
	}
	return sprite;
}

template<>
std::shared_ptr<Font> AssetManager::get<Font>(const std::string& name)
{
	std::shared_ptr<Font> font = _fontData.getElement(name);
	if (!font)
	{
		message("Could not get Font: " + name + ". Attempting to load Font from file.");
		font = load<Font>(name);
	}
	return font;
}

void AssetManager::clear()
{
	_textureData.clear();
	_spriteData.clear();
	_fontData.clear();
}

void AssetManager::message(const std::string& message)
{
	MSG("ASSETMANAGER: " << message);
}

void AssetManager::error(const std::string& err)
{
	ERR("ASSETMANAGER: " << err);
}