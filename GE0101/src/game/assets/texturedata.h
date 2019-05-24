#pragma once
#include "../../graphics/texture.h"
#include <vector>
#include <string>

class TextureData
{
	std::vector<Texture*>			_data;
public:
	TextureData();
	~TextureData();
	void loadTexture(const std::string& filepath);
	void pushTexture(Texture* texture);
	void popTexture(const std::string& name);
	const Texture* getTexture(const std::string& name) const;
};
