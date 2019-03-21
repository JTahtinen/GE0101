#pragma once
#include "texture.h"
#include "../math/vec2.h"
#include "../graphics/shader.h"
#include "../graphics/buffers/buffer.h"
#include "../graphics/buffers/indexbuffer.h"

struct Sprite
{
	Buffer*					vbo;
	const					IndexBuffer* indices;
	const Texture*			texture;
	Shader*					shader;
	std::string				name;
};