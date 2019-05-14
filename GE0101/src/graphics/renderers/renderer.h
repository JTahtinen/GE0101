#pragma once
#include "renderable.h"
#include "../buffers/vertexarray.h"
#include "../buffers/indexbuffer.h"
#include "../shader.h"
#include "../../defs.h"

struct Sprite;

class Renderer 
{
protected:
	Shader*			_shader;
public:
	virtual void submit(const Sprite* sprite, const Vec2& pos) = 0;
	virtual void submit(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos) = 0;
	virtual void flush() = 0;
	inline void setShader(Shader* shader) 
	{ 
		_shader = shader; 
		if (!_shader)
		{
			WARN("Could not set shader for renderer: nullptr exception");
		}
	}
};