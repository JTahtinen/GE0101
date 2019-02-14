#include "application.h"
#include "../math/math.h"
#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../util/log.h"
#include "../game/scenegraph.h"
#include "../util/file.h"
#include "SDL2/SDL_image.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
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

	Texture snowman("res/IMG_2086.png");
	snowman.bind(0);

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


	std::vector<Vec4> colors;
	colors.reserve(4);

	colors.push_back(Vec4(1.0f, 0, 0, 1.0f));
	colors.push_back(Vec4(0, 1.0f, 0, 1.0f));
	colors.push_back(Vec4(0, 0, 1.0f, 1.0f));
	colors.push_back(Vec4(1.0f, 1.0f, 0, 1.0f));


	colorBuffer.push(&colors[0], colors.size() * sizeof(Vec4));
	BufferLayout colorLayout;
	colorLayout.push<float>(4);
	vao.push(&colorBuffer, colorLayout);


	bool running = true;
	Vec2 pos(10, 10);

	Input& in = Input::instance();

	float r = 0;
	int dir = 1;
	while (running)
	{
		if (r <= 0)
		{
			dir = 1;
		}
		else if (r >= 1.0f)
		{
			dir = -1;
		}

		r += (float)dir * 0.0003f;

		shader.setUniform4f("u_Color", r, 0, 0, 1.0f);


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