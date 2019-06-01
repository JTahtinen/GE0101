#include "gamestate.h"
#include "../map.h"
#include "../game.h"
#include "../../input/input.h"
#include "../../physics/collider.h"
#include "../../defs.h"

GameState::GameState(const Game* game, Renderer* renderer)
	: _renderer(renderer)
	, _camera(renderer->getDisplayRatio())
	, _activeConversation(nullptr)
	, _substate(SUBSTATE_ACTIVE)
{
	_map = Map::createMap(5, 5, game);

}

GameState::~GameState()
{
	delete _map;
	for (auto* entity : _entities)
	{
		delete entity;
	}
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

		_map->update(game);

		for (auto& entity : _entities)
		{
			entity->update(this);
		}

		Collider::instance().update();

		_camera.setPos(_player->getPos());
		_camera.update();
		_map->render(_renderer, &_camera);

		for (auto& entity : _entities)
		{
			entity->render(_renderer, &_camera);
		}

		if (in.poll(KEY_E, KEYSTATE_TYPED))
		{
			_entities.back()->engage(this);
		}
		break;
	}
	case SUBSTATE_CONVERSATION:
	{
		if (!_activeConversation)
		{
			WARN("Could not init conversation");
			_activeConversation = nullptr;
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
	_map->render(_renderer, &_camera);

	for (auto& entity : _entities)
	{
		entity->render(_renderer, &_camera);
	}
	
	if (_substate == SUBSTATE_CONVERSATION)
	{
		_activeConversation->render(_renderer);
	}
	return STATE_RUNNING;
}
