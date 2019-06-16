#include "gamestate.h"
#include "../map.h"
#include "../game.h"
#include "../../input/input.h"
#include "../../physics/collider.h"
#include "../../defs.h"

GameState::GameState(Game& game)
	: 
	_camera(16.0f / 9.0f)
	, _activeConversation(nullptr)
	, _substate(SUBSTATE_ACTIVE)
{
	Map::init(game);
	//_map = std::shared_ptr<Map>(Map::loadMap("res/maps/testmap3.png", game));

}

GameState::~GameState()
{
	_entities.clear();
	Map::quit();
}

void GameState::addEntity(std::shared_ptr<Entity> e)
{
	if (!e)
	{
		WARN("Could not add entity to game state - nullptr exception");
		return;
	}
	_entities.push_back(e);
}

void GameState::addActor(std::shared_ptr<Actor> e)
{
	if (!e)
	{
		WARN("Could not add actor to game state - nullptr exception");
		return;
	}
	_actors.push_back(e);
	addEntity(e);
}

void GameState::setPlayer(std::shared_ptr<Actor> e)
{
	if (!e)
	{
		WARN("Could not set player - nullptr exception");
		return;
	}
	_player = e;
}

void GameState::setSubState(Game_Substate substate)
{
	_substate = substate;
}

void GameState::setMap(std::shared_ptr<Map> map)
{
	_map = map;
}

void GameState::setActiveConversation(std::shared_ptr<Conversation>& conversation)
{
	_activeConversation = conversation;
}

State_Condition GameState::update(Game& game)
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
			_entities.back()->engage(*this);
		}

		for (auto& entity : _entities)
		{
			entity->update(*this);
		}


		_camera.setPos(_player->getPhysics()->getPos().center + Vec2(0.1f, -0.1f));
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

	return STATE_RUNNING;
}

void GameState::render(Layer& layer)
{
	_map->render(layer, _camera);

	for (auto& entity : _entities)
	{
		entity->render(layer, _camera);
	}

	if (_substate == SUBSTATE_CONVERSATION)
	{
		_activeConversation->render(layer);
	}
}