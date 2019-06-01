#pragma once
#include "renderable.h"
#include "../font.h"

class TextRenderable : public Renderable
{
	std::vector<const Letter*>			_content;
	const Font*							_font;
	float								_scale;
public:
	TextRenderable() = default;
	TextRenderable(const std::string& text, const Font* font, const Vec4& pos, float scale, bool streaming = false);
	virtual void render(const Vec2& offset) const override;
	void setContent(const std::string& text);
	void setFont(const Font* font);
	inline void setScale(float scale) { _scale = scale; }
	static TextRenderable* createTextRenderable(const std::string& text, const Font* font, const Vec4& pos, float scale, bool streaming = false);
	static void init(const Renderer* renderer);
	static void quit();
protected:
	virtual void destroy() override;
};