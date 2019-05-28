#include "game.h"
#include "scenegraph.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"
#include "controllers/inputcontroller.h"
#include "controllers/aicontroller.h"
#include "../physics/collider.h"
#include "conversation.h"
#include "gamestate.h"

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
	node1->addOption("Go fuck yourself!", node3);
	node2->setText("It's such a nice evening!");
	node2->addOption("Indeed it is. Goodbye!", nullptr);
	node3->setText("Well, that's not very nice!");
	node3->addOption("I'm sorry. Ask me again.", node1);
	node3->addOption("Deal with it!", node4);
	node4->setText("No need to be an asshole!");

	conv->push(node1);
	conv->push(node2);
	conv->push(node3);
	conv->push(node4);


	Mesh* eMesh = new Mesh("defEntityMesh");
	TextureData& texData = _assetData.textureData;

	eMesh->bind();



	Vec2 vertData[] = {
		Vec2(-0.1f, -0.1f),
		Vec2(-0.1f,  0.1f),
		Vec2(0.1f, -0.1f),
		Vec2(0.1f, 0.1f)
	};

	Vec2 texCoordData[] = {
		Vec2(0, 1),
		Vec2(0, 0),
		Vec2(1, 1),
		Vec2(1, 0)
	};

	Vec4 colorData[]{
		Vec4(0.0f, 0, 0, 0),
		Vec4(0.0f, 0, 0, 0),
		Vec4(0.0f, 0, 0, 0),
		Vec4(0.0f, 0, 0, 0)
	};

	std::vector<unsigned int> indexData;
	indexData.push_back(0);
	indexData.push_back(1);
	indexData.push_back(2);
	indexData.push_back(2);
	indexData.push_back(3);
	indexData.push_back(1);


	Buffer* vertices = new Buffer();
	Buffer* texCoords = new Buffer();
	Buffer* colors = new Buffer();

	vertices->bind();
	vertices->push(&vertData[0], sizeof(vertData));

	texCoords->bind();
	texCoords->push(&texCoordData[0], sizeof(texCoordData));

	colors->bind();
	colors->push(&colorData[0], sizeof(colorData));

	BufferLayout layout;
	BufferLayout texCoordLayout;
	BufferLayout colorLayout;
	layout.push<float>(2);
	texCoordLayout.push<float>(2);
	colorLayout.push<float>(4);

	eMesh->pushData(vertices, layout);
	eMesh->pushData(texCoords, texCoordLayout);
	eMesh->pushData(colors, colorLayout);
	eMesh->setIndices(indexData);
	
	texData.loadTexture("res/textures/IMG_2086.png");
	texData.loadTexture("res/textures/cursor.png");

	_assetData.geometryData.pushGeometry(eMesh);
	
	Sprite* snowman = new Sprite(eMesh, texData.getTexture("res/textures/IMG_2086.png"), "snowman");
	Sprite* cursorSprite = new Sprite(eMesh, texData.getTexture("res/textures/cursor.png"), "cursor");
	_assetData.spriteData.pushSprite(snowman);
	_assetData.spriteData.pushSprite(cursorSprite);
	
	GameState* gameState = new GameState(this, renderer);
	Actor* player = new Actor(Vec2(), snowman, new InputController());
	gameState->addActor(player);
	gameState->setPlayer(player);
	gameState->addActor(new Actor(Vec2(-0.5f, -0.5f), snowman, new AIController(gameState)));
	Actor* a = new Actor(Vec2(0.5f, 0.5f), snowman);
	a->setConversation(conv);
	gameState->addActor(a);

	_cursor = Renderable2D::createRenderable2D(cursorSprite, Vec2(), 1.0f, true);
	
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
	_cursor->setPos(mousePos);
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
	_stateStack.pop_back();
}

const AssetData* Game::getAssetData() const
{
	return &_assetData;
}