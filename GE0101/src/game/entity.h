#pragma once
#include "../math/vec2.h"
#include "../graphics/sprite.h"
#include "../graphics/renderers/renderer.h"

class Game;

typedef unsigned int GUID;

class Controller;

class Entity
{
protected:
	friend class Controller;
	GUID				_id;
	Sprite*				_sprite;
	Vec2				_pos{ Vec2(0, 0) };
	Vec2				_vel{ Vec2(0, 0) };
	const Controller*	_controller{ nullptr };

public:
	Entity(const Vec2& pos, Sprite* sprite);
	Entity(const Vec2& pos);
	Entity();
	void setVel(const Vec2& vel);
	void addVel(const Vec2& vel);
	inline const Vec2& getPos() const { return _pos; }
	virtual ~Entity(); 
	virtual void update(Game* game);
	void addController(const Controller* controller);
	void render(Renderer* renderer, const Camera* camera) const;
private:
	static GUID nextId();
};