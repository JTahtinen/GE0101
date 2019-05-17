#pragma once
#include <string>

class Texture
{
	unsigned int			_id;
	const std::string		_filepath;
	int						_widthInPixels;
	int						_heightInPixels;
public:
	Texture(const std::string& filepath);
	~Texture();
	void bind(unsigned int slot = 0) const;
	void unbind() const;
	inline int getWidthInPixels() const
	{
		return _widthInPixels;
	}
	inline int getHeightInPixels() const
	{
		return _heightInPixels;
	}
};