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

Game::Game(std::shared_ptr<Layer> layer)
	: _layer(layer)
{
	ASSERT(layer);

	std::shared_ptr<Conversation> conv = std::make_shared<Conversation>();
	std::shared_ptr<ConvNode> node1 = std::make_shared<ConvNode>();
	std::shared_ptr<ConvNode> node2 = std::make_shared<ConvNode>();
	std::shared_ptr<ConvNode> node3 = std::make_shared<ConvNode>();
	std::shared_ptr<ConvNode> node4 = std::make_shared<ConvNode>();
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


	auto texData = _assetData.textureData;

	
	texData.loadTexture("res/textures/guy.png");
	texData.loadTexture("res/textures/cursor1.png");
	texData.loadTexture("res/textures/floor.png");
	texData.loadTexture("res/textures/wall.png");

	
	
	std::shared_ptr<Sprite> guy = std::make_shared<Sprite>( Sprite{ texData.getTexture("res/textures/guy.png"), Vec2(0.2f, 0.2f), "guy" });
	_cursor = std::make_shared<Sprite>(Sprite { texData.getTexture("res/textures/cursor1.png"), Vec2(0.2f, 0.2f), "cursor" });
	std::shared_ptr<Sprite> floor = std::make_shared<Sprite>( Sprite { texData.getTexture("res/textures/floor.png"), Vec2(0.2f, 0.2f), "floor" });
	std::shared_ptr<Sprite> wall = std::make_shared<Sprite>(Sprite{ texData.getTexture("res/textures/wall.png"), Vec2(0.2f, 0.2f), "wall" });

	_assetData.spriteData.addSprite(guy);
	_assetData.spriteData.addSprite(_cursor);
	_assetData.spriteData.addSprite(floor);
	_assetData.spriteData.addSprite(wall);

	std::shared_ptr<GameState> gameState = std::make_shared<GameState>(*this, layer);
	std::shared_ptr<Actor> player = std::make_shared<Actor>(Vec2(0.4f, 0.2f), guy, std::make_shared<InputController>());
	gameState->addActor(player);
	gameState->setPlayer(player);
	//gameState->addActor(new Actor(Vec2(-0.5f, -0.5f), snowman, new AIController(gameState)));
	gameState->addActor(std::make_shared<Actor>(Vec2(0.5f, 0.7f), guy));
	gameState->addActor(std::make_shared<Actor>(Vec2(0.3f, 0.7f), guy));
	gameState->addActor(std::make_shared<Actor>(Vec2(0.82f, 0.74f), guy));
	gameState->addActor(std::make_shared<Actor>(Vec2(0.2f, 0.23f), guy));
	std::shared_ptr<Actor> a = std::make_shared<Actor>(Vec2(0.5f, 0.5f), guy, std::make_shared<AIController>(gameState));
	a->setConversation(conv);
	gameState->addActor(a);
	
	//_cursor = Renderable2D::createRenderable2D(cursorSprite, Vec4(), 0.5f, true);
	
	_stateStack.push_back(gameState);
}

Game::~Game()
{
	_stateStack.clear();
}


void Game::update(float frameTime)
{
	Game::frameTime = frameTime;
	static Input& in = Input::instance();
	static auto& win = _layer->getWindow();
	static int winHeight = win->getHeight();
	Vec2 mousePos = win->getScreenCoordsRatioCorrected(in.getMouseX(), winHeight - in.getMouseY());
	//_cursor->setPos(Vec4(mousePos.x, mousePos.y, 1, 1));
	auto& state = _stateStack.back();
	state->update(*this);	
	_layer->submitSprite(_cursor, mousePos, Vec3(0, 0, -1));
}

void Game::pushState(std::shared_ptr<State> state)
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