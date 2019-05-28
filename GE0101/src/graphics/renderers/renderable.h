#pragma once
#include "../sprite.h"
#include "../../math/math.h"
#include "../font.h"
#include <vector>
#include "../shader.h"
#include "../mesh.h"

class Renderer;

extern void initRenderables(const Renderer* renderer);
extern void destroyRenderables();

class VertexArray;
class IndesBuffer;
class Texture;

class Renderable
{
	friend class Renderer;
	friend class Renderable2D;
	friend class TextRenderable;
	friend class QuadRenderable;
protected:
	unsigned int						_tag;
	bool								_streaming;
	Vec2								_pos;
	std::vector<Renderable*>			_children;
public:
	Renderable() {}
	Renderable(const Vec2& pos, bool streaming = false);
	void addChild(Renderable* child);
	virtual void render(const Vec2& offset) const = 0;
	void setPos(const Vec2& pos) { _pos = pos; }
	void setTag(unsigned int tag);
	inline bool isStreaming() const
	{
		return _streaming;
	}
	void freeRenderable();
protected:
	virtual void destroy() = 0;
};

class Renderable2D : public Renderable
{
	const Sprite*		_sprite;
	float				_scale;
public:
	Renderable2D() = default;
	Renderable2D(const Sprite* sprite, const Vec2& pos, float scale, bool streaming = false);
	static Renderable2D* createRenderable2D(const Sprite* sprite, const Vec2& pos, float scale, bool streaming = false);
	virtual void render(const Vec2& offset) const override;
protected:
	virtual void destroy() override;
};


class TextRenderable : public Renderable
{
	std::vector<const Letter*>			_content;
	const Font*							_font;
	float								_scale;
public:
	TextRenderable() = default;
	TextRenderable(const std::string& text, const Font* font, const Vec2& pos, float scale, bool streaming = false);
	virtual void render(const Vec2& offset) const override;
	void setContent(const std::string& text);
	void setFont(const Font* font);
	inline void setScale(float scale) { _scale = scale; }
	static TextRenderable* createTextRenderable(const std::string& text, const Font* font, const Vec2& pos, float scale, bool streaming = false);
protected:
	virtual void destroy() override;
};

class QuadRenderable : public Renderable
{
	Vec2				_dimensions;
	Vec4				_color;
public:
	QuadRenderable() = default;
	QuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color, bool streaming = false);
	QuadRenderable(const Vec2& pos, const Vec2& dimensions, bool streaming = false);
	static QuadRenderable* createQuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color, bool streaming = false);
	static QuadRenderable* createQuadRenderable(const Vec2& pos, const Vec2& dimensions, bool streaming = false);
	virtual void render(const Vec2& offset) const override;
protected:
	virtual void destroy() override;
};