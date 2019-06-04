#pragma once
#include "../../math/vec2.h"
#include "../../graphics/sprite.h"
#include "../../graphics/layer.h"
#include "../../physics/physicsobject.h"
#include "../conversation.h"
#include <string>
#include <sstream>

class Camera;
class GameState;
class Game;

typedef unsigned int GUID;

class Entity
{
	friend class Map;
	friend class Controller;
protected:
	GUID				_id;
	PhysicsObject		_object;
	Sprite*				_sprite;
	Conversation*		_conversation;
	bool				_engaged;
public:
	Entity(const Vec2& pos, Sprite* sprite);
	Entity(const Vec2& pos);
	Entity();
	virtual ~Entity();
	void move(const Vec2& dir, float amt);
	void stopMoving();
	void setConversation(Conversation* conversation);
	inline const PhysicsObject* getPhysics() const { return &_object; }
	virtual void update(GameState* gamestate);
	void engage(GameState* gamestate);
	void render(Layer* layer, const Camera* camera) const;
	inline GUID getId() const { return _id; }
	inline std::string getName() const 
	{
		std::stringstream ss;
		ss << _id;
		return ss.str();
	}
private:
	static GUID nextId();
};