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

Game::Game(Renderer* renderer)
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


	//_assetData.geometryData.pushGeometry()
	TextureData& texData = _assetData.textureData;

	Mesh* eMesh = new Mesh("defEntityMesh");
	eMesh->bind();
	_assetData.geometryData.pushGeometry(eMesh);

	Vec2 vertData[] = {
		Vec2(-1.0f, -1.0f),
		Vec2(-1.0f,  1.0f),
		Vec2(1.0f, -1.0f),
		Vec2(1.0f, 1.0f)
	};

	Vec2 texCoordData[] = {
		Vec2(0, 0),
		Vec2(0, 1),
		Vec2(1, 1),
		Vec2(1, 0)
	};

	Vec4 colorData[]{
		Vec4(1, 0, 0, 0),
		Vec4(1, 0, 0, 0),
		Vec4(1, 0, 0, 0),
		Vec4(1, 0, 0, 0)
	};

	std::vector<unsigned int> indexData;
	indexData.push_back(0);
	indexData.push_back(1);
	indexData.push_back(2);
	indexData.push_back(2);
	indexData.push_back(3);
	indexData.push_back(1);


	Buffer vertices;
	vertices.push(&vertData[0], sizeof(vertData));
	vertices.push(&texCoordData[0], sizeof(texCoordData));
	vertices.push(&colorData[0], sizeof(colorData));
	BufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	layout.push<float>(4);
	eMesh->pushData(&vertices, layout, indexData);
	texData.loadTexture("res/textures/IMG_2086.png");
	Sprite* snowman = new Sprite(eMesh, texData.getTexture("res/textures/IMG_2086.png"), "snowman");
	_gameData.pushSprite(snowman);
//	conv.start();
	ASSERT(renderer);
	_map = Map::createMap(5, 5, &_gameData);
	Actor* player = new Actor(Vec2(0.0f, 0.0f), snowman, new InputController());
	addActor(player);
	_player = player;
	addActor(new Actor(Vec2(-0.5f, -0.5f), snowman, new AIController(this)));
	addActor(new Actor(Vec2(0.5f, 0.5f), snowman));
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

 	_camera.setPos(_player->getPos());
	_camera.update();
	_map->render(_renderer, &_camera);
	for (auto& entity : _entities)
	{
		entity->render(_renderer, &_camera);
	}

	//QuadRenderable* cursor = QuadRenderable::createQuadRenderable(Vec2(0, 0), Vec2(0.2f, 0.2f));
	Renderable2D* cursor = Renderable2D::createRenderable2D(_gameData.getSprite("snowman"), Vec2(0, 0), 1.0f);
	_renderer->submit(cursor);
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
