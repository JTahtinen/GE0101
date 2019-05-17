#pragma once
#include "renderer.h"
#include <string>
#include <vector>
#include "../font.h"
#include "../../math/vec2.h"

struct Word
{
	Vec2 pos;
	std::vector<const Letter*> letters;
};

class TextRenderer : public Renderer
{
	std::vector<Word>					_renderables;
	const Font*							_font;
	Vec2								_cursor;
public:
	TextRenderer(const Font* font);
	void setFont(const Font* font);
	void submit(const std::string& text, const Vec2& pos);
	virtual void flush() override;
};