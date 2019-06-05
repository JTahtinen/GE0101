#pragma once
#include "renderer.h"
#include "../../math/math.h"
#include <string>
#include <vector>
#include "textbatch.h"

struct LetterData;

class TextRenderer : public Renderer
{
	LetterData*						_buffer;
	std::vector<TextBatch>			_batches;
public:
	TextRenderer(Window* win);
	void submit(const std::string& label, const Vec2& pos, const float scale, const Font* font);
	void flush() override;
	static void init(Window* win);
	static void quit();
};