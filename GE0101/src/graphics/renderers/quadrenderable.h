#pragma once
#include "renderable.h"

class QuadRenderable : public Renderable
{
	Vec2				_dimensions;
	Vec4				_color;
public:
	QuadRenderable() = default;
	QuadRenderable(const Vec4& pos, const Vec2& dimensions, const Vec4& color, bool streaming = false);
	QuadRenderable(const Vec4& pos, const Vec2& dimensions, bool streaming = false);
	static QuadRenderable* createQuadRenderable(const Vec4& pos, const Vec2& dimensions, const Vec4& color, bool streaming = false);
	static QuadRenderable* createQuadRenderable(const Vec4& pos, const Vec2& dimensions, bool streaming = false);
	virtual void render(const Vec2& offset) const override;
	static void init(const Renderer* renderer);
	static void quit();
protected:
	virtual void destroy() override;
};