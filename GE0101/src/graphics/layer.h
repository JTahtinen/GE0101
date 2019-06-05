#pragma once
#include "renderers/batchrenderer.h"
#include "window.h"
#include <vector>

class Layer
{
	Window*						_win;
	BatchRenderer*				_batchRenderer;

public:
	Layer(Window* win);
	void submitSprite(const Sprite* sprite, const Vec2& pos, const Vec3& offset);
	void submitText(const std::string& label, const Vec2& pos);
	void submitQuad(const Vec4& color, const Vec2& dimensions, const Vec2& pos);
	void begin();
	void end();
	void flush();
	inline const Window* getWindow() const { return _win; }
	inline float getDisplayRatio() const { return _win->getRatio(); }
	inline BatchRenderer* getBatchRenderer() { return _batchRenderer; }
};