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
	std::shared_ptr<Map>					_map;
	std::vector<std::shared_ptr<Entity>>	_entities;
	std::vector<std::shared_ptr<Actor>>		_actors;
	std::shared_ptr<Actor>					_player;
	Camera									_camera;
	std::shared_ptr<Conversation>			_activeConversation;
	Game_Substate							_substate;
public:
	GameState(Game& game);
	virtual ~GameState() override;
	void addEntity(std::shared_ptr<Entity> e);
	void addActor(std::shared_ptr<Actor> e);
	void setPlayer(std::shared_ptr<Actor> e);
	void setSubState(Game_Substate substate);
	void setMap(std::shared_ptr<Map> map);
	void setActiveConversation(std::shared_ptr<Conversation>& conversation);
	virtual State_Condition update(Game& game) override;
	inline auto& getEntities() const { return _entities; }
	inline auto getMap() const { return _map; }
	inline std::shared_ptr<const Actor> getPlayer() const { return _player; }
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const override;
	virtual void render(Layer& layer) override;
};