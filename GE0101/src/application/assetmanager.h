#pragma once
#include "../util/assetcollection.h"
#include "../graphics/font.h"
#include "../graphics/texture.h"
#include "../graphics/sprite.h"

class AssetManager
{
	AssetCollection<Font>		_fontData;
	AssetCollection<Texture>	_textureData;
	AssetCollection<Sprite>		_spriteData;
public:
	template<typename T>
	AssetCollection<T>& getData();
	template<typename T>
	std::shared_ptr<T> load(const std::string& filepath);
};