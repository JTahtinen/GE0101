#pragma once
#include <string>

class AssetManager;

class Texture
{
	unsigned int			_id;
	const std::string		_filepath;
	int						_widthInPixels;
	int						_heightInPixels;
public:
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
	inline const std::string& getFilePath() const
	{
		return _filepath;
	}
	inline unsigned int getId() const { return _id; }
	static std::shared_ptr<Texture> loadTexture(const std::string& filepath);
private:
	Texture(const std::string& filepath);
};