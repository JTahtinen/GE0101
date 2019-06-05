#pragma once

#include "renderable.h"
#include "renderable2d.h"
#include "quadrenderable.h"
#include "textrenderable.h"

#include "../window.h"
#include <string>
#include "../buffers/indexbuffer.h"

enum Texture_Slot
{
	TEXTURE_SLOT_UNBIND = 0,
	TEXTURE_SLOT_SPRITE,
	TEXTURE_SLOT_FONT_ATLAS,
	TEXTURE_SLOT_AMOUNT
};

class Renderer
{
	Window*						_win;
protected:
	unsigned int				_vao;
	unsigned int				_vbo;
public:
	Renderer(Window* window);
	virtual ~Renderer();
	virtual void flush() = 0;
	virtual void begin();
	virtual void end();
	
protected:
	void clear();
	void update();
	//void destroyRenderable(Renderable* renderable);
};