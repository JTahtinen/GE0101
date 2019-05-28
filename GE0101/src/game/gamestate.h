#pragma once
#include "state.h"
#include "camera.h"
#include "gamedata.h"
#include "actor.h"
#include <vector>

class Map;
class GameData;
class Renderer;

class GameState : public State
{
	Map*					_map;
	std::vector<Entity*>	_entities;
	std::vector<Actor*>		_actors;
	Actor*					_player;
	GameData				_gameData;
	Camera					_camera;
	Renderer*				_renderer;
	Conversation*			_activeConversation;
public:
	GameState(const Game* game, Renderer* renderer);
	~GameState();
	void addEntity(Entity* e);
	void addActor(Actor* e);
	void setPlayer(Actor* e);
	const Actor* getPlayer() const;
	virtual State_Condition update(Game* game) override;
};