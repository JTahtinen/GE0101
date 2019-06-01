#include "renderable.h"
#include "../../defs.h"
#include "../../globals.h"
#include "../buffers/vertexarray.h"
#include "renderer.h"
#include "renderable2d.h"
#include "quadrenderable.h"
#include "textrenderable.h"

void initRenderables(const Renderer* renderer)
{
	Renderable2D::init(renderer);
	QuadRenderable::init(renderer);
	TextRenderable::init(renderer);
}

void destroyRenderables()
{
	Renderable2D::quit();
	QuadRenderable::quit();
	TextRenderable::quit();
}


Renderable::Renderable(const Vec4& pos, bool streaming)
	: _pos(pos)
	, _streaming(streaming)
{
	_children.reserve(20);
}

void Renderable::addChild(Renderable* child)
{
	if (!child)
	{
		WARN("Could not add child for renderable - nullptr exception");
		return;
	}
	_children.push_back(child);
}

void Renderable::setTag(unsigned int tag)
{
	_tag = tag;
}

void Renderable::freeRenderable()
{
	_streaming = false;
}