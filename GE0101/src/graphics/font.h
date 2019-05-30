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
	std::vector<Letter> _letters;
	Texture*			_atlas{ nullptr };
public:
	~Font();
	static Font* loadFont(const std::string& filepath);
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
	inline const Texture* getAtlas() const
	{
		return _atlas;
	}
	void bind() const;
private:
	Font(std::vector<Letter> letters, Texture* atlas);
};