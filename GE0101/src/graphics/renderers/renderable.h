#pragma once
#include "../sprite.h"
#include "../../math/math.h"
#include "../font.h"
#include <vector>
#include "../shader.h"

extern void initRenderables();
extern void destroyRenderables();

class VertexArray;
class IndesBuffer;
class Texture;

class Renderable
{
protected:
	unsigned int						_tag;
	Vec2								_pos;
	std::vector<Renderable*>			_children;
public:
	Renderable(const Vec2& pos);
	void addChild(Renderable* child);
	virtual void render() const = 0;
	virtual void destroy() = 0;
	void setTag(unsigned int tag);
};

class Renderable2D : public Renderable
{
	const VertexArray*	_vao;
	const IndexBuffer*	_ibo;
	const Texture*		_texture;
public:
	Renderable2D(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos);
	static Renderable2D* createRenderable2D(const VertexArray* vao, const IndexBuffer* ibo, const Texture* texture, const Vec2& pos);
	static Renderable2D* createRenderable2D(const Sprite* sprite, const Vec2& pos);
	virtual void render() const override;
	virtual void destroy() override;
};


class TextRenderable : public Renderable
{
	std::vector<const Letter*>			_content;
	const Font*							_font;
public:
	TextRenderable(const std::string& text, const Font* font, const Vec2& pos);
	virtual void render() const override;
	static TextRenderable* createTextRenderable(const std::string& text, const Font* font, const Vec2& pos);
	virtual void destroy() override;
};

class QuadRenderable : public Renderable
{
	Vec2				_dimensions;
	Vec4				_color;
public:
	QuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color);
	QuadRenderable(const Vec2& pos, const Vec2& dimensions);
	static QuadRenderable* createQuadRenderable(const Vec2& pos, const Vec2& dimensions, const Vec4& color);
	static QuadRenderable* createQuadRenderable(const Vec2& pos, const Vec2& dimensions);
	virtual void render() const override;
	virtual void destroy() override;
//	QuadRenderable operator=(const QuadRenderable& other) const;
};