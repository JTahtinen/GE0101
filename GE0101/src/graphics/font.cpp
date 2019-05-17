#include "font.h"
#include "../util/file.h"
#include "../defs.h"
#include <sstream>
#include <string>

Font::~Font()
{
	delete _atlas;
}

Font* Font::loadFont(const std::string& filepath)
{
	std::string fontfile = load_text_file(filepath + ".fnt");

	if (fontfile == "")
	{
		ERR("Could not open font file: " << filepath << ".fnt");
		return nullptr;
	} 

	Texture* atlas = new Texture(filepath + ".png");
	
	if (!atlas)
	{
		ERR("Could not open font atlas: " << filepath << ".png");
		return nullptr;
	}

	int texWidth = atlas->getWidthInPixels();
	int texHeight = atlas->getHeightInPixels();

	std::istringstream ss(fontfile);
	std::string line;
	std::vector<Letter> letters;
	int i = 0;
	bool firstIdSkipped = false;
	while (ss >> line)
	{
		std::istringstream word(line);
		getline(word, line, '=');
		if (line == "id")
		{
			if (!firstIdSkipped)
			{
				// Skip first "id=" in the font file, as it is not relevant
				firstIdSkipped = true;
				continue;
			}
			letters.emplace_back(Letter{ 0 });
			getline(word, line);
			letters[i].character = stoi(line);
		} else 
		if (line == "x")
		{
			getline(word, line);
			letters[i].x = stof(line) / (float)texWidth;
		}	else 
		if (line == "y")
		{
			getline(word, line);
			letters[i].y = stof(line) / (float)texHeight;
		} else 
		if (line == "width")
		{
			getline(word, line);
			letters[i].width = stof(line) / (float)texWidth;
		}
		else
		if (line == "height")
		{
			getline(word, line);
			letters[i].height = stof(line) / (float)texHeight;
		} else
		if (line == "xoffset")
		{
			getline(word, line);
			letters[i].xOffset = stof(line) / (float)texWidth;
		}
		else
		if (line == "yoffset")
		{
			getline(word, line);
			letters[i].yOffset = stof(line) / (float)texHeight;
		}
		else
		if (line == "xadvance")
		{
			getline(word, line);
			letters[i++].xAdvance = stof(line) / (float)texWidth;
		}
		

	}

	return new Font(letters, atlas);
}

Font::Font(std::vector<Letter> letters, Texture* atlas)
	: _letters(letters)
	, _atlas(atlas)
{
}