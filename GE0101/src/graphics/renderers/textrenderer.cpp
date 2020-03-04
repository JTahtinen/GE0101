#include "textrenderer.h"
#include "../../defs.h"


struct LetterData
{
	Vec2 pos;
	Vec2 dimensions;
	Vec2 offset;
	Vec2 texCoord;
	float scale;
};

enum ShaderAttributeIndex
{
	SHADER_INDEX_POSITION = 0,
	SHADER_INDEX_DIMENSIONS,
	SHADER_INDEX_OFFSET,
	SHADER_INDEX_TEXCOORD,
	SHADER_INDEX_SCALE
};


#define RENDERER_MAX_LABELS 60000
#define RENDERER_LETTER_SIZE sizeof(LetterData)
#define RENDERER_BUFFER_SIZE (RENDERER_LETTER_SIZE * RENDERER_MAX_LABELS)



TextRenderer::TextRenderer(Window* win)
	: Renderer(win)
	, _shader("res/shaders/letter", true)
{
	_shader.bind();
	_shader.setUniform1f("u_ScreenRatio", win->getRatio());
	_shader.setUniform1f("u_ScreenRatio", win->getRatio());
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_INDEX_POSITION);
	glEnableVertexAttribArray(SHADER_INDEX_DIMENSIONS);
	glEnableVertexAttribArray(SHADER_INDEX_OFFSET);
	glEnableVertexAttribArray(SHADER_INDEX_TEXCOORD);
	glEnableVertexAttribArray(SHADER_INDEX_SCALE);

	glVertexAttribPointer(SHADER_INDEX_POSITION, 2, GL_FLOAT, GL_FALSE, RENDERER_LETTER_SIZE, (const void*)0);
	glVertexAttribPointer(SHADER_INDEX_DIMENSIONS, 2, GL_FLOAT, GL_FALSE, RENDERER_LETTER_SIZE, (const void*)(2 * sizeof(float)));
	glVertexAttribPointer(SHADER_INDEX_OFFSET, 2, GL_FLOAT, GL_FALSE, RENDERER_LETTER_SIZE, (const void*)(4 * sizeof(float)));
	glVertexAttribPointer(SHADER_INDEX_TEXCOORD, 2, GL_FLOAT, GL_FALSE, RENDERER_LETTER_SIZE, (const void*)(6 * sizeof(float)));
	glVertexAttribPointer(SHADER_INDEX_SCALE, 1, GL_FLOAT, GL_FALSE, RENDERER_LETTER_SIZE, (const void*)(8 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TextRenderer::submit(const std::string& label, const Vec2& pos, const float scale, std::shared_ptr<const Font> font)
{
	for (auto& batch : _batches)
	{
		if (batch.checkCompatibility(*font))
		{
			batch.submit(label, pos, scale);
			return;
		}
	}
	_batches.emplace_back(TextBatch(font));
	_batches.back().submit(label, pos, scale);
}

void TextRenderer::flush()
{
	
	_shader.bind();
	
	glBindVertexArray(_vao);
	for (const auto& batch : _batches)
	{
		unsigned int numLetters = 0;
		auto& data = batch.getData();
		batch.bindFont();
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		const auto font = batch.getFont();
	//	float scale = batch.getScale();
		_shader.setUniform1i("u_Texture", TEXTURE_SLOT_FONT_ATLAS);
	//	_shader.setUniform1f("u_Base", batch.getFont()->getBase() * scale);
		_shader.setUniform1f("u_Base", batch.getFont()->getBase());
		_buffer = (LetterData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//		_shader.setUniform1f("u_Scale", scale);
		for (const auto& renderable : data)
		{
			const std::string& text = renderable.content;
			float cursor = 0;
			for (const char c : text)
			{
				const auto l = font->getLetter(c);
				if (!l)
				{
					continue;
				}

				_buffer->pos = renderable.pos + Vec2(cursor, 0);
				_buffer->dimensions = Vec2(l->width, l->height);
				_buffer->texCoord = Vec2(l->x, l->y);
				_buffer->offset = Vec2(l->xOffset, l->yOffset);
				_buffer->scale = renderable.scale;
				++_buffer;

				cursor += l->xAdvance * renderable.scale;
				++numLetters;
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glDrawArrays(GL_POINTS, 0, numLetters);
	}
	for (auto& batch : _batches)
	{
		batch.clear();
	}
}

/*
void TextRenderer::init(const Window& win)
{
	shader = new Shader("res/shaders/letter", true);
	shader->bind();
	shader->setUniform1f("u_ScreenRatio", win.getRatio());
}

void TextRenderer::quit()
{
	delete shader;
	shader = nullptr;
}
*/