#include "application.h"
#include "../math/vec2.h"
#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../util/log.h"
#include "../game/scenegraph.h"

Log gameLog;

Application::Application()
	: _window(800, 600, "GE0101")
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	std::vector<Vec2> vertices;
	vertices.push_back(Vec2(-0.5f, -0.5f));
	vertices.push_back(Vec2( 0.0f,	0.5f));
	vertices.push_back(Vec2( 0.5f, -0.5f));

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec2), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), (const void*)0);
	glEnableVertexAttribArray(0);
}

void Application::run()
{
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
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);
		_window.update();
	}

}