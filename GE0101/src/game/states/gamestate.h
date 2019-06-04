#pragma once
#include "state.h"
#include "../camera.h"
#include "../entity/actor.h"
#include <vector>

class Map;
class GameData;
class Layer;

enum Game_Substate
{
	SUBSTATE_ACTIVE,
	SUBSTATE_CONVERSATION
};


class GameState : public State
{
	Map*									_map;
	std::vector<Entity*>					_entities;
	std::vector<Actor*>						_actors;
	Actor*									_player;
	Camera									_camera;
	Layer*									_layer;
	Conversation*							_activeConversation;
	Game_Substate							_substate;
public:
	GameState(const Game* game, Layer* layer);
	virtual ~GameState() override;
	void addEntity(Entity* e);
	void addActor(Actor* e);
	void setPlayer(Actor* e);
	const Actor* getPlayer() const;
	void setSubState(Game_Substate substate);
	void setActiveConversation(Conversation* conversation);
	virtual State_Condition update(Game* game) override;
	inline const std::vector<Entity*>& getEntities() const { return _entities; }
	inline const Map* getMap() const { return _map; }
};