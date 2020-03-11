#pragma once
#include "renderer.h"
#include "../shader.h"
#include "../polygon.h"
#include "../buffers/indexbuffer.h"
#include "polygonbatch.h"

struct VertexData;

class MeshRenderer : public Renderer
{
	Shader											_shader;
	VertexData*										_buffer;
	std::vector<PolygonBatch>						_batches;
public:
	MeshRenderer(Window* win);
	void submit(const Polygon& renderable, const Vec2& pos, const Vec3& offset);
	virtual void flush() override;
};