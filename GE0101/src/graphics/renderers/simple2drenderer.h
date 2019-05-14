#pragma once
#include "renderer.h"
#include <vector>

class Simple2DRenderer : public Renderer
{
	std::vector<Renderable> _renderables;
public:
	Simple2DRenderer();
	virtual void submit(const Sprite* sprite, const Vec2& pos) override;
	void submit(const VertexArray* vbo, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos) override;
	virtual void flush() override;
};