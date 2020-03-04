#include "label.h"
#include "../globals.h"

Label::Label(const std::string& content, std::shared_ptr<const Font> font)
	: _content(content)
	, _font(font)
{
}

Label::Label(const std::string& content)
	: _content(content)
	, _font(g_assetManager.get<Font>("res/fonts/arial"))
{

}