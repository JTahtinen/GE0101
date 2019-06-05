#include "renderer.h"
#include "../../defs.h"

Renderer::Renderer(Window* window)
	: _win(window)
{
	ASSERT(_win);
}

Renderer::~Renderer()
{
	delete _win;
	_win = nullptr;
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
}

void Renderer::begin()
{
	clear();
}

void Renderer::end()
{	

}

void Renderer::clear()
{
	_win->clear();
}

void Renderer::update()
{
	_win->update();
}
/*
void Renderer::destroyRenderable(Renderable* renderable)
{
	renderable->destroy();
}*/