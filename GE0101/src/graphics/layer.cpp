#include "layer.h"
#include "../defs.h"

Layer::Layer(Window* win)
	: _win(win)
{
	_batchRenderer = std::make_unique<BatchRenderer>(win);
	_textRenderer = std::make_unique<TextRenderer>(win);
}

Layer::~Layer()
{
}

void Layer::submitSprite(std::shared_ptr<const Sprite> sprite, const Vec2& pos, const Vec3& offset)
{
	_batchRenderer->submit(sprite, pos, offset);
}

void Layer::submitText(const std::string& label, const Vec2& pos, const float scale, std::shared_ptr<const Font> font)
{
	_textRenderer->submit(label, pos, scale, font);
}

void Layer::submitQuad(const Vec4& color, const Vec2& dimensions, const Vec2& pos)
{
	//TODO: Batch rendering for quads
}

void Layer::begin()
{
	_win->clear();

	_batchRenderer->begin();
	_textRenderer->begin();
}

void Layer::end()
{

	_batchRenderer->end();
	_textRenderer->end();
}
void Layer::flush()
{
	_batchRenderer->flush();
	_textRenderer->flush();
	_win->update();

}