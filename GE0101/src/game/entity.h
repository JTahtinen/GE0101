#pragma once
#include "../math/vec2.h"
#include "../graphics/surface.h"
class Game;

typedef unsigned int GUID;

class Entity
{
protected:
	GUID				_id;
	const Surface*		_sprite;
	Vec2				_pos{ Vec2(0, 0) };
	Vec2				_vel{ Vec2(0, 0) };
public:
	Entity(const Vec2& pos, const Surface* sprite);
	Entity(const Surface* sprite);
	Entity();
	inline const Vec2& getPos() const { return _pos; }
	inline const Surface* getSprite() const { return _sprite; }
	virtual ~Entity(); 
	virtual void update(Game* game);
private:
	static GUID nextId();
};