#pragma once
#include "renderer.h"
#include "../buffers/vertexarray.h"
#include "../buffers/indexbuffer.h"
#include "../sprite.h"
#include "../../math/vec3.h"

struct VertexData;

class BatchRenderer : public Renderer
{
	unsigned int _vao;
	unsigned int _vbo;
	IndexBuffer _ibo;
	VertexData* _buffer;
	unsigned int _indexCount;
public:
	BatchRenderer(Window* win);
	~BatchRenderer();
	void begin() override;
	void end() override;
	void submit(const Sprite* renderable, const Vec2& pos, const Vec3& offset);
	virtual void flush() override;
	static void init(const Window* win);
	static void quit();
	void setOffset(const Vec3& offset);
};