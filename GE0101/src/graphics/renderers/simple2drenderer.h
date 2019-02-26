#pragma once
#include "renderer.h"
#include <vector>

class Simple2DRenderer : public Renderer
{
	std::vector<const Renderable*> _renderables;
	std::vector<unsigned int>      _indices;
public:
	Simple2DRenderer();
	virtual void submit(const Renderable* renderable) override;
	virtual void flush() override;
};