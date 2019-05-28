#pragma once

#include <vector>
#include "renderable.h"
#include "../window.h"
#include <string>

class Renderer 
{
	Window						_win;
	std::vector<Renderable*>	_renderables;
public:
	Renderer(int width, int height, const std::string& title);
	~Renderer();
	void submit(Renderable* renderable);
	void flush();
	inline const Window* getWindow() const { return &_win; }
	inline float getDisplayRatio() const { return _win.getRatio(); }
};
