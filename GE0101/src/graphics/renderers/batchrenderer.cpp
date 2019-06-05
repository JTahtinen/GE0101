#include "batchrenderer.h"
#include "../shader.h"

static Shader* shader;

struct VertexData
{
	Vec2 pos;
	Vec2 texCoord;
	Vec4 color;
	Vec3 offset;
};

enum ShaderAttributeIndex
{
	SHADER_INDEX_POSITION = 0,
	SHADER_INDEX_TEXCOORD,
	SHADER_INDEX_COLOR,
	SHADER_INDEX_OFFSET
};



#define RENDERER_MAX_SPRITES 60000
#define RENDERER_VERTEX_SIZE sizeof(VertexData)
#define RENDERER_SPRITE_SIZE (RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE (RENDERER_MAX_SPRITES * 6)



BatchRenderer::BatchRenderer(Window* win)
	: Renderer(win)
{
	_spriteBatches.reserve(30);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_INDEX_POSITION);
	glEnableVertexAttribArray(SHADER_INDEX_TEXCOORD);
	glEnableVertexAttribArray(SHADER_INDEX_COLOR);
	glEnableVertexAttribArray(SHADER_INDEX_OFFSET);
	glVertexAttribPointer(SHADER_INDEX_POSITION, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)0);
	glVertexAttribPointer(SHADER_INDEX_TEXCOORD, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(2 * sizeof(float)));
	glVertexAttribPointer(SHADER_INDEX_COLOR,	 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(4 * sizeof(float)));
	glVertexAttribPointer(SHADER_INDEX_OFFSET, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(8 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	unsigned int* vertices = new unsigned int[RENDERER_INDICES_SIZE];
	for (unsigned int i = 0; i < RENDERER_MAX_SPRITES; ++i)
	{
		unsigned int offset = i * 4;
		vertices[i * 6 + 0] = 0 + offset;
		vertices[i * 6 + 1] = 1 + offset;
		vertices[i * 6 + 2] = 2 + offset;
		vertices[i * 6 + 3] = 2 + offset;
		vertices[i * 6 + 4] = 3 + offset;
		vertices[i * 6 + 5] = 0 + offset;
	}
	_ibo.bind();
	_ibo.push(vertices, RENDERER_INDICES_SIZE);
	delete[] vertices;
	vertices = nullptr;
}

BatchRenderer::~BatchRenderer()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

//void BatchRenderer::submit(const Sprite* renderable, const Vec2& pos, const Vec3& offset)
void BatchRenderer::submit(const Sprite* renderable, const Vec2& pos, const Vec3& offset)
{
	for (auto& batch : _spriteBatches)
	{
		if (batch.checkCompatibility(renderable))
		{
			batch.submit(renderable, pos, offset);
			return;
		}
	}
	_spriteBatches.emplace_back(SpriteBatch(renderable->texture));
	_spriteBatches.back().submit(renderable, pos, offset);
	
}



void BatchRenderer::flush()
{
	shader->bind();
	glBindVertexArray(_vao);
	_ibo.bind();
	for (const auto& batch : _spriteBatches)
	{
		unsigned int indexCount = 0;
		auto& data = batch.getData();
		batch.bindTexture(TEXTURE_SLOT_SPRITE);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (const auto& renderable : data)
		{
			const Sprite* sprite = renderable.sprite;
			const Vec2& pos = renderable.pos;
			const Vec3& offset = renderable.offset;

			const Vec2& size = sprite->size;
			float halfW = size.x * 0.5f;
			float halfH = size.y * 0.5f;

			_buffer->pos = Vec2(pos.x - halfW, pos.y - halfH);
			_buffer->texCoord = Vec2(0, 1);
			_buffer->color = Vec4(0, 0, 0, 0);
			_buffer->offset = offset;
			++_buffer;

			_buffer->pos = Vec2(pos.x - halfW, pos.y + halfH);
			_buffer->texCoord = Vec2(0, 0);
			_buffer->color = Vec4(0, 0, 0, 0);
			_buffer->offset = offset;
			++_buffer;

			_buffer->pos = Vec2(pos.x + halfW, pos.y + halfH);
			_buffer->texCoord = Vec2(1, 0);
			_buffer->color = Vec4(0, 0, 0, 0);
			_buffer->offset = offset;
			++_buffer;

			_buffer->pos = Vec2(pos.x + halfW, pos.y - halfH);
			_buffer->texCoord = Vec2(1, 1);
			_buffer->color = Vec4(0, 0, 0, 0);
			_buffer->offset = offset;
			++_buffer;

			indexCount += 6;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	}
	for (auto& batch : _spriteBatches)
	{
		batch.clear();
	}
}

void BatchRenderer::init(const Window* window)
{
	shader = new Shader("res/shaders/basic");
	shader->bind();
	shader->setUniform4f("u_Color", 0, 0.0f, 0.1f, 0);
	shader->setUniform3f("u_Offset", 0, 0, 0);
	shader->setUniform1f("u_ScrRatio", window->getRatio());
	shader->setUniform1f("u_Scale", 1.0f);
	shader->setUniform1i("u_Texture", TEXTURE_SLOT_SPRITE);
}

void BatchRenderer::quit()
{
	delete shader;
	shader = nullptr;
}

void BatchRenderer::setOffset(const Vec3& offset)
{
	shader->bind();
	//shader->setUniform3f("u_Offset", offset.x, offset.y, offset.z);
}