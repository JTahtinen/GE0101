#include "game.h"
#include "scenegraph.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"
#include "entity/controllers/inputcontroller.h"
#include "entity/controllers/aicontroller.h"
#include "../physics/collider.h"
#include "conversation.h"
#include "states/gamestate.h"

float Game::frameTime = 0.0f;

Game::Game(Renderer* renderer)
	: _renderer(renderer)
{
	ASSERT(renderer);

	Conversation* conv = new Conversation();
	ConvNode* node1 = new ConvNode();
	ConvNode* node2 = new ConvNode();
	ConvNode* node3 = new ConvNode();
	ConvNode* node4 = new ConvNode();
	node1->setText("How are you?");
	node1->addOption("I'm quite fine.", node2);
	node1->addOption("Mind your own business!", node3);
	node2->setText("It's such a nice evening!");
	node2->addOption("Indeed it is. Goodbye!", nullptr);
	node3->setText("Well, that's not very nice!");
	node3->addOption("I'm sorry. Ask me again.", node1);
	node3->addOption("Deal with it!", node4);
	node4->setText("No need to be rude!");

	conv->push(node1);
	conv->push(node2);
	conv->push(node3);
	conv->push(node4);


	Mesh* eMesh = new Mesh("defEntityMesh");
	TextureData& texData = _assetData.textureData;

	eMesh->bind();



	float vertData[] = {
		-0.1f, -0.1f,
		0, 1,
		1.0f, 0, 0, 0.0f,

		-0.1f,  0.1f,
		0, 0,
		0.0f, 0, 0, 0,
		
		0.1f, -0.1f,
		1, 1,
		0.0f, 0, 0, 0,
		
		0.1f, 0.1f,
		1, 0,
		0.0f, 0, 0, 0
	};
/*
	Vec2 texCoordData[] = {
	};

	Vec4 colorData[]{
	};
*/
	std::vector<unsigned int> indexData;
	indexData.push_back(0);
	indexData.push_back(1);
	indexData.push_back(2);
	indexData.push_back(2);
	indexData.push_back(3);
	indexData.push_back(1);


	Buffer* vertices = new Buffer();
	//Buffer* texCoords = new Buffer();
//	Buffer* colors = new Buffer();

	vertices->bind();
	vertices->push(&vertData[0], sizeof(vertData));

	//texCoords->bind();
//	texCoords->push(&texCoordData[0], sizeof(texCoordData));
	//vertices->push(&texCoordData[0], sizeof(texCoordData));
//	colors->bind();
//	colors->push(&colorData[0], sizeof(colorData));
	//vertices->push(&colorData[0], sizeof(colorData));
	BufferLayout layout;
	//BufferLayout texCoordLayout;
	//BufferLayout colorLayout;
	layout.push<float>(2);
	layout.push<float>(2);
	layout.push<float>(4);
	//texCoordLayout.push<float>(2);
	//colorLayout.push<float>(4);

	eMesh->pushData(vertices, layout);
	//eMesh->pushData(texCoords, texCoordLayout);
	//eMesh->pushData(colors, colorLayout);
	eMesh->setIndices(indexData);
	
	texData.loadTexture("res/textures/guy.png");
	texData.loadTexture("res/textures/cursor1.png");
	texData.loadTexture("res/textures/floor.png");
	texData.loadTexture("res/textures/wall.png");

	_assetData.geometryData.pushGeometry(eMesh);
	
	Sprite* guy = new Sprite(eMesh, texData.getTexture("res/textures/guy.png"), "guy");
	Sprite* cursorSprite = new Sprite(eMesh, texData.getTexture("res/textures/cursor1.png"), "cursor");
	Sprite* floor = new Sprite(eMesh, texData.getTexture("res/textures/floor.png"), "floor");
	Sprite* wall = new Sprite(eMesh, texData.getTexture("res/textures/wall.png"), "wall");

	_assetData.spriteData.pushSprite(guy);
	_assetData.spriteData.pushSprite(cursorSprite);
	_assetData.spriteData.pushSprite(floor);
	_assetData.spriteData.pushSprite(wall);

	GameState* gameState = new GameState(this, renderer);
	Actor* player = new Actor(Vec2(0.4f, 0.2f), guy, new InputController());
	gameState->addActor(player);
	gameState->setPlayer(player);
	//gameState->addActor(new Actor(Vec2(-0.5f, -0.5f), snowman, new AIController(gameState)));
	gameState->addActor(new Actor(Vec2(0.5f, 0.7f), guy));
	gameState->addActor(new Actor(Vec2(0.3f, 0.7f), guy));
	gameState->addActor(new Actor(Vec2(0.82f, 0.74f), guy));
	gameState->addActor(new Actor(Vec2(0.2f, 0.23f), guy));
	Actor* a = new Actor(Vec2(0.5f, 0.5f), guy, new AIController(gameState));
	a->setConversation(conv);
	gameState->addActor(a);

	_cursor = Renderable2D::createRenderable2D(cursorSprite, Vec4(), 0.5f, true);
	
	_stateStack.push_back(gameState);
}

Game::~Game()
{
	for (auto& state : _stateStack)
	{
		delete state;
	}
	_stateStack.clear();
	_cursor->freeRenderable();
}


void Game::update(float frameTime)
{
	Game::frameTime = frameTime;
	static Input& in = Input::instance();
	static const Window* win = _renderer->getWindow();
	static int winHeight = win->getHeight();
	Vec2 mousePos = win->getScreenCoordsRatioCorrected(in.getMouseX(), winHeight - in.getMouseY());
	_cursor->setPos(Vec4(mousePos.x, mousePos.y, 1, 1));
	State* state = _stateStack.back();
	state->update(this);	
	_renderer->submit(_cursor);
}

void Game::pushState(State* state)
{
	_stateStack.push_back(state);
}

void Game::popState()
{
	State* state = _stateStack.back();
	delete state;
	_stateStack.pop_back();
}

const AssetData* Game::getAssetData() const
{
	return &_assetData;
}