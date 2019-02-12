#pragma once
#include <string>

class Texture
{
	static unsigned int		_numTextures{ 0 };
	unsigned int			_id;
	const std::string		_filepath;
public:
	Texture(const std::string& filepath);
};