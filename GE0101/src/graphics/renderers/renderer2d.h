#pragma once
#include "renderable.h"
#include "renderer.h"
#include "../buffers/vertexarray.h"
#include "../buffers/indexbuffer.h"


struct Sprite;

class Renderer2D : public Renderer
{
protected:
	std::vector<Renderable> _renderables;
public:
	Renderer2D();
	virtual void submit(const Sprite* sprite, const Vec2& pos) = 0;
	virtual void submit(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos) = 0;
	virtual void flush() override;
};