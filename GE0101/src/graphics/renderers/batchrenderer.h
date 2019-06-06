#pragma once
#include "renderer.h"
#include "../buffers/vertexarray.h"
#include "../buffers/indexbuffer.h"
#include "../sprite.h"
#include "../../math/vec3.h"
#include "spritebatch.h"

struct VertexData;

class BatchRenderer : public Renderer
{
	VertexData*						_buffer;
	std::vector<SpriteBatch>		_spriteBatches;
	IndexBuffer						_ibo;
public:
	BatchRenderer(Window* win);
	~BatchRenderer();
	void submit(std::shared_ptr<const Sprite> renderable, const Vec2& pos, const Vec3& offset);
	virtual void flush() override;
	static void init(const Window& win);
	static void quit();
};