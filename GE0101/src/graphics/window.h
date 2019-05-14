#pragma once
#include <SDL2\SDL.h>
#include <GLEW/glew.h>


class Window
{
	SDL_Window*		_win;
	SDL_GLContext	_glContext;
	int				_width;
	int				_height;
public:
	Window(int width, int height, const char* title);
	~Window();
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
	void setClearColor(GLclampf r, GLclampf g, GLclampf b);
	void clear() const;
	void update() const;
	void setTitle(const char* title);
};