#pragma once
#include "../math/vec2.h"
#include "../graphics/sprite.h"
#include "../graphics/renderers/renderer.h"
#include "collider.h"

class Game;

typedef unsigned int GUID;

class Entity
{
protected:
	friend class Controller;
	GUID				_id;
	Sprite*				_sprite;
	Collider*			_collider;
	Vec2				_pos{ Vec2(0, 0) };
	Vec2				_vel{ Vec2(0, 0) };
public:
	Entity(const Vec2& pos, Sprite* sprite);
	Entity(const Vec2& pos);
	Entity();
	virtual ~Entity();
	void setVel(const Vec2& vel);
	void addVel(const Vec2& vel);
	inline const Vec2& getPos() const { return _pos; } 
	inline const Vec2& getVel() const { return _vel; }
	inline const Collider* getCollider() const { return _collider; }
	virtual void update(Game* game);
	void render(Renderer* renderer, const Camera* camera) const;
private:
	static GUID nextId();
};