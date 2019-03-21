#pragma once
#include "renderable.h"

struct Sprite;

class Renderer 
{
public:
	virtual void submit(const Sprite* sprite, const Vec2& pos) = 0;
	virtual void flush() = 0;
};