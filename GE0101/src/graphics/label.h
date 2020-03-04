#pragma once
#include <string>
#include "font.h"

class Label
{
	std::string							_content;
	std::shared_ptr<const Font>			_font;
public:
	Label(const std::string& content, std::shared_ptr<const Font> font);
	Label(const std::string& content);
};