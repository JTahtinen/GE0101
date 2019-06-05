#include "gamestate.h"
#include "../map.h"
#include "../game.h"
#include "../../input/input.h"
#include "../../physics/collider.h"
#include "../../defs.h"

GameState::GameState(const Game* game, Layer* layer)
	: _layer(layer)
	, _camera(layer->getDisplayRatio())
	, _activeConversation(nullptr)
	, _substate(SUBSTATE_ACTIVE)
{
	Map::init(game);
	_map = Map::loadMap("res/maps/testmap3.png", game);

}

GameState::~GameState()
{
	delete _map;
	for (auto* entity : _entities)
	{
		delete entity;
	}
	_entities.clear();
	Map::quit();
}

void GameState::addEntity(Entity* e)
{
	if (!e)
	{
		WARN("Could not add entity to game state - nullptr exception");
		return;
	}
	_entities.push_back(e);
}

void GameState::addActor(Actor* e)
{
	if (!e)
	{
		WARN("Could not add actor to game state - nullptr exception");
		return;
	}
	_actors.push_back(e);
	addEntity(e);
}

void GameState::setPlayer(Actor* e)
{
	if (!e)
	{
		WARN("Could not set player - nullptr exception");
		return;
	}
	_player = e;
}

const Actor* GameState::getPlayer() const
{
	return _player;
}

void GameState::setSubState(Game_Substate substate)
{
	_substate = substate;
}

void GameState::setActiveConversation(Conversation* conversation)
{
	_activeConversation = conversation;
}

State_Condition GameState::update(Game* game)
{
	static Input& in = Input::instance();

	switch (_substate)
	{

	case SUBSTATE_ACTIVE:
	{
		if (in.poll(KEY_Z, KEYSTATE_TYPED) || in.getMouseWheelUp())
		{
			_camera.zoomIn();
		}
		if (in.poll(KEY_X, KEYSTATE_TYPED) || in.getMouseWheelDown())
		{
			_camera.zoomOut();
		}
		if (in.poll(KEY_E, KEYSTATE_TYPED))
		{
			_entities.back()->engage(this);
		}

		for (auto& entity : _entities)
		{
			entity->update(this);
		}


		_camera.setPos(_player->getPhysics()->getPos().center);
		_camera.update();
	
		break;
	}
	case SUBSTATE_CONVERSATION:
	{
		if (!_activeConversation)
		{
			WARN("Could not init conversation");
			_substate = SUBSTATE_ACTIVE;
			break;
		}
		Conversation_Status convStatus = _activeConversation->update();
		if (convStatus == CONVERSATION_FINISHED)
		{
			_activeConversation = nullptr;
			_substate = SUBSTATE_ACTIVE;
			break;
		}
	}
	}
	_map->render(_layer, &_camera);

	for (auto& entity : _entities)
	{
		entity->render(_layer, &_camera);
	}
	
	if (_substate == SUBSTATE_CONVERSATION)
	{
		_activeConversation->render(_layer);
	}
	return STATE_RUNNING;
}
