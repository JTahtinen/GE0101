#include "application.h"
#include "../math/vec2.h"
#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../util/log.h"
#include "../game/scenegraph.h"
#include "../util/file.h"
#include "SDL2/SDL_image.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../graphics/shader.h"

Log gameLog;

std::vector<unsigned int> indices;

Application::Application()
	: _window(800, 600, "GE0101")
{


}

void Application::run()
{
	VertexArray vao;
	Buffer vbo;
	Buffer colorBuffer;
	Buffer texCoordBuffer;
	BufferLayout layout;


	//Vertex data
	std::vector<Vec2> vertices;
	vertices.push_back(Vec2(-0.8f, 0.8f));
	vertices.push_back(Vec2(0.8f, 0.8f));
	vertices.push_back(Vec2(0.8f, -0.8f));
	vertices.push_back(Vec2(-0.8f, -0.8f));

	vbo.push(&vertices[0], vertices.size() * sizeof(Vec2));
	layout.push<float>(2);
	vao.push(&vbo, layout);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(3);

	IndexBuffer ibo;	
	ibo.push(&indices[0], indices.size());

	//Shaders

	Shader shader("res/shaders/basic");
	shader.bind();

	//Textures

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	IMG_Init(IMG_INIT_PNG);

	SDL_Surface* texImage = IMG_Load("res/IMG_2086.png");

	if (!texImage)
	{
		__debugbreak();
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texImage->w, texImage->h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texImage->pixels);
	SDL_FreeSurface(texImage);


	Vec2 texCoords[] = {
		Vec2(0, 0),
		Vec2(1, 0),
		Vec2(1, 1),
		Vec2(0, 1)
	};

	shader.setUniform1i("u_Texture", 0);
	shader.setUniform4f("u_Color", 1.0f, 0, 1.0f, 1.0f);

	texCoordBuffer.push(&texCoords[0], 4 * sizeof(Vec2));
	BufferLayout texCoordLayout;
	texCoordLayout.push<float>(2);
	vao.push(&texCoordBuffer, texCoordLayout);


	float colors[] =
	{
		1.0f, 0,	0,		1.0f,
		0	, 1.0f, 0,		1.0f,
		0	, 0,	1.0f,	1.0f,
		1.0f, 1.0f, 0,		1.0f,
	};

	colorBuffer.push(&colors[0], 16 * sizeof(float));
	BufferLayout colorLayout;
	colorLayout.push<float>(4);
	vao.push(&colorBuffer, colorLayout);


	bool running = true;
	Vec2 pos(10, 10);

	Input& in = Input::instance();

	while (running)
	{
		in.update();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}

		_game.update();
		_window.clear();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
		_window.update();
	}

}