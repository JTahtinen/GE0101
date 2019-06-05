#pragma once
#include "../../math/math.h"
#include <vector>

class Renderer;

extern void initRenderables(const Renderer* renderer);
extern void destroyRenderables();

#define RENDERABLE_POOL_SIZE 1000

#define RENDER_CHILDREN() for (auto& child : _children)\
{ if (child) {child->render(Vec2(_pos.x, _pos.y));} }
#define DESTROY_CHILDREN() for (auto& child : _children)\
{ if (child) {if (!child->isStreaming()) {child->destroy();}}} _children.clear();

/*class Renderable
{
	friend class Renderer;
	friend class Renderable2D;
	friend class TextRenderable;
	friend class QuadRenderable;
protected:
	unsigned int						_tag;
	bool								_streaming;
	Vec4								_pos;
	std::vector<Renderable*>			_children;
public:
	Renderable() {}
	Renderable(const Vec4& pos, bool streaming = false);
	void addChild(Renderable* child);
	virtual void render(const Vec2& offset) const = 0;
	void setPos(const Vec4& pos) { _pos = pos; }
	void setTag(unsigned int tag);
	inline bool isStreaming() const
	{
		return _streaming;
	}
	void freeRenderable();
protected:
	virtual void destroy() = 0;
};

template <typename T> 
T* createRenderable(T* pool, std::vector<unsigned int>& availableRenderables, unsigned int* tag)
{
	if (!availableRenderables.empty())
	{
		unsigned int i = availableRenderables.back();
		availableRenderables.pop_back();
		T* renderable = &pool[i];
		*tag = i;
		return renderable;
	}
	return nullptr;
}*/