#pragma once
#include "renderable.h"
#include "../sprite.h"

class Renderable2D : public Renderable
{
	const Sprite*		_sprite;
	float				_scale;
public:
	Renderable2D() = default;
	Renderable2D(const Sprite* sprite, const Vec4& pos, float scale, bool streaming = false);
	static Renderable2D* createRenderable2D(const Sprite* sprite, const Vec4& pos, float scale, bool streaming = false);
	virtual void render(const Vec2& offset) const override;
	static void init(const Renderer* renderer);
	static void quit();
protected:
	virtual void destroy() override;
};