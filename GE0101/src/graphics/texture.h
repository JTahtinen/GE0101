#pragma once
#include <string>

class Texture
{
	unsigned int			_id;
	const std::string		_filepath;
public:
	Texture(const std::string& filepath);
	~Texture();
	void bind(unsigned int slot = 0) const;
	void unbind() const;
};