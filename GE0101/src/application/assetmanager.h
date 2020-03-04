#pragma once
#include "../util/assetcollection.h"

class Font;
class Texture;
class Sprite;

class AssetManager
{
	AssetCollection<Font>		_fontData;
	AssetCollection<Texture>	_textureData;
	AssetCollection<Sprite>		_spriteData;
public:
	~AssetManager();
	template<typename T>
	std::shared_ptr<T> load(const std::string& filepath);
	template<typename T>
	void add(std::shared_ptr<T> element, const std::string& name);
	template<typename T>
	void remove(const std::string& name);
	template<typename T>
	std::shared_ptr<T> get(const std::string& name);
	void clear();
private:
	void message(const std::string& msg);
	void error(const std::string& err);
};