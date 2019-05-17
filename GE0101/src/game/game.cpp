#include "game.h"
#include "scenegraph.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"
#include "controllers/inputcontroller.h"
#include "controllers/aicontroller.h"
#include "../physics/collider.h"
#include "conversation.h"

float Game::frameTime = 0.0f;

Game::Game(Renderer2D* renderer)
	: _camera(Camera(16.0f, 9.0f))
	, _renderer(renderer)
{
	Conversation conv;
	ConvNode node1;
	ConvNode node2;
	ConvNode node3;
	ConvNode node4;
	node1.setText("How are you?");
	node1.addOption("I'm quite fine.", &node2);
	node1.addOption("Go fuck yourself!", &node3);
	node2.setText("It's such a nice evening!");
	node2.addOption("Indeed it is. Goodbye!", nullptr);
	node3.setText("Well, that's not very nice!");
	node3.addOption("I'm sorry. Ask me again.", &node1);
	node3.addOption("Deal with it!", &node4);
	node4.setText("No need to be an asshole!");
	
	conv.push(&node1);
	conv.push(&node2);
	conv.push(&node3);
	conv.push(&node4);
//	conv.start();
	ASSERT(renderer);
	_map = Map::createMap(5, 5);
	Actor* player = new Actor(Vec2(0.0f, 0.0f), &defaultSprite, new InputController());
	addActor(player);
	_player = player;
	addActor(new Actor(Vec2(-0.5f, -0.5f), &defaultSprite, new AIController(this)));
	addActor(new Actor(Vec2(0.5f, 0.5f), &defaultSprite));
}

Game::~Game()
{
	delete _map;
	for (auto* entity : _entities)
	{
		delete entity;
	}
}

void Game::update(float frameTime)
{
	Game::frameTime = frameTime;
	//MSG(frameTime);
	static Input& in = Input::instance();
	if (in.poll(KEY_Z, KEYSTATE_TYPED))
	{
		_camera.zoomIn();
	}
	if (in.poll(KEY_X, KEYSTATE_TYPED))
	{
		_camera.zoomOut();
	}
	_map->update(this);
	
	for (auto& entity : _entities)
	{
		entity->update(this);
	}

	Collider::instance().update();
//	_player->getPos().print();

 	_camera.setPos(_player->getPos());
	_camera.update();
	_map->render(_renderer, &_camera);
	for (auto& entity : _entities)
	{
		entity->render(_renderer, &_camera);
	}
}

void Game::addEntity(Entity* e)
{
	if (e)
	{
		_entities.push_back(e);
	}
}

void Game::addActor(Actor* e)
{
	if (e)
	{
		_actors.push_back(e);
		addEntity(e);
	}
}

const Camera& Game::getCamera() const
{
	return _camera;
}

const Actor* Game::getPlayer() const
{
	return _player;
}

const std::vector<Entity*>& Game::getEntities() const
{
	return _entities;
}
