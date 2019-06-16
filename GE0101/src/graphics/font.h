#pragma once
#include <vector>
#include "../graphics/texture.h"

struct Letter
{
	char character;
	float x, y;
	float width, height;
	float xOffset, yOffset;
	float xAdvance;
};

class Font
{
	unsigned int				_id;
	std::vector<Letter>			_letters;
	std::shared_ptr<Texture>	_atlas;
public:
	~Font();
	static std::shared_ptr<Font> loadFont(const std::string& filepath);
	inline const Letter* getLetter(char letter) const
	{
		for (auto& l : _letters)
		{
			if (l.character == letter)
			{
				return &l;
			}
		}
		return nullptr;
	}
	inline std::shared_ptr<const Texture> getAtlas() const
	{
		return _atlas;
	}
	void bind() const;
	inline unsigned int getId() const { return _id; }
public:
	Font(std::vector<Letter> letters, std::shared_ptr<Texture> atlas);
	static unsigned int nextId();
};