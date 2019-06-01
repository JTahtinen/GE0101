#pragma once

#include <vector>
#include "renderable.h"
#include "renderable2d.h"
#include "quadrenderable.h"
#include "textrenderable.h"
#include "../window.h"
#include <string>

enum Texture_Slot
{
	TEXTURE_SLOT_UNBIND = 0,
	TEXTURE_SLOT_SPRITE,
	TEXTURE_SLOT_FONT_ATLAS,
	TEXTURE_SLOT_AMOUNT
};

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
