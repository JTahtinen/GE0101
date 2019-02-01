#include "window.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
	: _width(width)
	, _height(height)
{
	if (_width < 100)
	{
		_width = 100;
	}
	if (_height < 100)
	{
		_height = 100;
	}

	if (_width > 2000)
	{
		_width = 2000;
	}
	if (_height > 2000)
	{
		_height = 2000;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


	_win = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		_width, 
		_height, 
		SDL_WINDOW_OPENGL);
	_glContext = SDL_GL_CreateContext(_win);

	GLenum status = glewInit();
	setClearColor(0.3f, 0.1f, 0.8f);
}

Window::~Window()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_win);
}

void Window::update() const
{
	SDL_GL_SwapWindow(_win);
}

void Window::setClearColor(GLclampf r, GLclampf g, GLclampf b)
{
	glClearColor(r, g, b, 1.0f);
}

void Window::clear() const
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
}