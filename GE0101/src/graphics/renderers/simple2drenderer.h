#pragma once
#include "renderer2d.h"
#include <vector>

class Simple2DRenderer : public Renderer2D
{
public:
	virtual void submit(const Sprite* sprite, const Vec2& pos) override;
	void submit(const VertexArray* vbo, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos) override;
};