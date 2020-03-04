#pragma once
#include "../../math/vec2.h"
#include "../../graphics/sprite.h"
#include "../../graphics/layer.h"
#include "../../physics/physicsobject.h"
#include "../conversation.h"
#include "components/component.h"
#include "components/graphicscomponent.h"
#include <string>
#include <vector>
#include <sstream>

class Camera;
class Game;
class Game;

typedef unsigned int GUID;

enum EntityCommand
{
	COMMAND_MOVE_UP,
	COMMAND_MOVE_DOWN,
	COMMAND_MOVE_LEFT,
	COMMAND_MOVE_RIGHT,
	COMMAND_INCREASE_SPEED,

};

class Entity
{
	friend class Map;
	friend class Controller;
	friend class GraphicsComponent;
	friend class AnimatedGraphicsComponent;
protected:
	GUID								_id;
	PhysicsObject						_object;
	std::shared_ptr<const Sprite>		_sprite;
	std::shared_ptr<GraphicsComponent>	_graphics{ nullptr };
	std::shared_ptr<Conversation>		_conversation;
	std::vector<EntityCommand>			_commandList;
	bool								_engaged;
	float								_normalSpeed;
	float								_increasedSpeed;
	float								_currentSpeed;
public:
	Entity(const Vec2& pos, std::vector<std::shared_ptr<const Sprite>> frames);
	Entity(const Vec2& pos, std::shared_ptr<const Sprite> sprite);
	Entity(const Vec2& pos);
	Entity();
	virtual ~Entity();
	void init();
	void addCommand(EntityCommand command);
	void move(const Vec2& dir, float amt);
	void stopMoving();
	void setConversation(std::shared_ptr<Conversation> conversation);
	inline const PhysicsObject* getPhysics() const { return &_object; }
	virtual void update(Game& gamestate);
	void engage(Game& gamestate);
	void render(Layer& layer, const Camera& camera) const;
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