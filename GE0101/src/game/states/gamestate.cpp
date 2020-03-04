#include "gamestate.h"
#include "../map.h"
#include "../game.h"
#include "../../input/input.h"
#include "../../physics/collider.h"
#include "../../defs.h"
#include "../../application/application.h"
#include "../../util/file.h"
#include "../../globals.h"
#include "../entity/controllers/inputcontroller.h"

GameState::GameState(Application& app)
	: 
	_camera(16.0f / 9.0f)
	, _activeConversation(nullptr)
	, _substate(SUBSTATE_ACTIVE)
{
	
	//_map = std::shared_ptr<Map>(Map::loadMap("res/maps/testmap3.png", game));

}

GameState::~GameState()
{
	_entities.clear();
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

State_Condition GameState::update(Application& app)
{
	static Input& in = Input::instance();
	if (in.pollKeyboard(KEY_Q, KEYSTATE_TYPED))
	{
		return STATE_FINISHED;
	}

	switch (_substate)
	{

	case SUBSTATE_ACTIVE:
	{
		if (in.pollKeyboard(KEY_Z, KEYSTATE_TYPED) || in.getMouseWheelUp())
		{
			_camera.zoomIn();
		}
		if (in.pollKeyboard(KEY_X, KEYSTATE_TYPED) || in.getMouseWheelDown())
		{
			_camera.zoomOut();
		}
		if (in.pollKeyboard(KEY_E, KEYSTATE_TYPED))
		{
			_entities.back()->engage(*this);
		}

		for (auto& entity : _entities)
		{
			entity->update(*this);
		}

		const Vec2& playerDimensions = _player->getPhysics()->getPos().dimensions;

		_camera.setPos(_player->getPhysics()->getPos().center + Vec2(0.1f, 0.1f));
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

Vec2 GameState::getInContextPosition(const Vec2& screenPosition) const
{
	//Vec2 projectedMousePos(screenPosition.x * 0.5f + 0.5f, screenPosition.y * 0.5f + 0.5f);
	Vec2 projectedMousePos(math::projectToCoordinates(screenPosition.x, -1.0f, 1.0f, 0, 1.0f)
		, math::projectToCoordinates(screenPosition.y, -1.0f, 1.0f, 0, 1.0f));
	return _camera.getWorldPoint(projectedMousePos);
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

std::unique_ptr<GameState> GameState::loadGameState(const std::string& filepath, Application& app)
{
	std::unique_ptr<GameState> gameState = std::make_unique<GameState>(app);
	std::string file = load_text_file(filepath);
	std::istringstream ss(file);
	std::string line;
	while (ss >> line)
	{
		if (line == "map:")
		{
			ss >> line;
			gameState->setMap(std::shared_ptr<Map>(Map::loadMap(line, app)));
			continue;
		}
		if (line == "player:")
		{
			ss >> line;
			float x = stof(line);
			ss >> line;
			float y = stof(line);
			ss >> line;
			//	auto sprite = assets.get<Sprite>(line);
			std::vector<std::shared_ptr<const Sprite>> animFrames;
			animFrames.reserve(5);
			animFrames.push_back(g_assetManager.get<Sprite>("res/sprites/stationary.sprite"));
			animFrames.push_back(g_assetManager.get<Sprite>("res/sprites/left.sprite"));
			animFrames.push_back(g_assetManager.get<Sprite>("res/sprites/up.sprite"));
			animFrames.push_back(g_assetManager.get<Sprite>("res/sprites/right.sprite"));
			animFrames.push_back(g_assetManager.get<Sprite>("res/sprites/down.sprite"));
			std::shared_ptr<Actor> player = std::make_shared<Actor>(Vec2((float)x, (float)y), animFrames, std::make_shared<InputController>());
			gameState->addActor(player);
			gameState->setPlayer(player);
			continue;
		}
		if (line == "e:")
		{
			ss >> line;
			float x = stof(line);
			ss >> line;
			float y = stof(line);
			ss >> line;
			gameState->addActor(std::make_shared<Actor>(Vec2((float)x, (float)y), g_assetManager.get<Sprite>(line)));
			continue;
		}
	}
	return gameState;
}
