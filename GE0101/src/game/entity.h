#pragma once
#include "../math/vec2.h"
#include "../graphics/sprite.h"
#include "../graphics/renderers/renderer.h"
#include "../physics/physicsobject.h"
#include "conversation.h"
#include <string>
#include <sstream>

class Camera;
class GameState;
class Game;

typedef unsigned int GUID;

class Entity
{
protected:
	friend class Controller;
	GUID				_id;
	PhysicsObject		_object;
	Sprite*				_sprite;
	Conversation*		_conversation;
public:
	Entity(const Vec2& pos, Sprite* sprite);
	Entity(const Vec2& pos);
	Entity();
	virtual ~Entity();
	void setForce(const Vec2& force);
	void addForce(const Vec2& force);
	void setConversation(Conversation* conversation);
	inline const Vec2& getPos() const { return _object.location.pos; } 
	inline const Vec2& getForce() const { return _object.force; }
	inline const Vec2& getDimensions() const { return _object.location.dimensions; }
	inline bool isMoving() const { return _object.force.length() != 0; }
	virtual void update(GameState* gamestate);
	Conversation* engage();
	void render(Renderer* renderer, const Camera* camera) const;
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