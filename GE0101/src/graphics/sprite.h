#pragma once
#include "texture.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/indexbuffer.h"

struct Sprite
{
	VertexArray*			vao;
	const IndexBuffer*		indices;
	const Texture*			texture;
	std::string				name;
};