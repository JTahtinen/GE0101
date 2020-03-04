#pragma once
#include <SDL2\SDL.h>
#include <GLEW/glew.h>
#include "../math/vec2.h"

class Window
{
	SDL_Window*		_win;
	SDL_GLContext	_glContext;
	int				_width;
	int				_height;
	bool			_fullScreen;
public:
	Window(int width, int height, const char* title, bool fullScreen);
	~Window();
	inline int getWidth() const { return _width; }
	inline int getHeight() const { return _height; }
	void update() const;
	void setClearColor(GLclampf r, GLclampf g, GLclampf b);
	void clear() const;
	void setTitle(const char* title);
	void toggleFullScreen();
	inline float getRatio() const
	{
		return (float)_width / (float)_height;
	}
	inline Vec2 getScreenCoords(int x, int y) const
	{
		float halfW = _width * 0.5f;
		float halfH = _height * 0.5f;
		return Vec2((float)(x - halfW) / halfW, (float)(y - halfH) / halfH);
	}

	inline Vec2 getScreenCoordsRatioCorrected(int x, int y) const
	{
		Vec2 vec = getScreenCoords(x, y);
		
		return Vec2(vec.x, vec.y * ((float)_height / (float)_width));
	}

private:
	void setFullScreen(bool fullScreen);
};