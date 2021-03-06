//
//#include "game.h"
//#include "scenegraph.h"
//#include "../input/input.h"
//#include "../defs.h"
//#include "../globals.h"
//#include "entity/controllers/inputcontroller.h"
//#include "entity/controllers/aicontroller.h"
//#include "../physics/collider.h"
//#include "conversation.h"
//#include "states/menustate.h"
//#include "states/gamestate.h"
//#include "../util/file.h"
//#include "../application/assetmanager.h"
//
//
//
//float Game::frameTime = 0.0f;
//
//Game::Game(AssetManager& assets)
//	: _curStateIndex(0)
//{
//	_states.reserve(2);
//
//	/*std::shared_ptr<Conversation> conv = std::make_shared<Conversation>();
//	std::shared_ptr<ConvNode> node1 = std::make_shared<ConvNode>();
//	std::shared_ptr<ConvNode> node2 = std::make_shared<ConvNode>();
//	std::shared_ptr<ConvNode> node3 = std::make_shared<ConvNode>();
//	std::shared_ptr<ConvNode> node4 = std::make_shared<ConvNode>();
//	node1->setText("How are you?");
//	node1->addOption("I'm quite fine.", node2);
//	node1->addOption("Mind your own business!", node3);
//	node2->setText("It's such a nice evening!");
//	node2->addOption("Indeed it is. Goodbye!", nullptr);
//	node3->setText("Well, that's not very nice!");
//	node3->addOption("I'm sorry. Ask me again.", node1);
//	node3->addOption("Deal with it!", node4);
//	node4->setText("No need to be rude!");
//
//	conv->push(node1);
//	conv->push(node2);
//	conv->push(node3);
//	conv->push(node4);
//*/
//
//	/*
//	Texture::loadTexture("res/textures/cursor1.png", assets);
//	Texture::loadTexture("res/textures/floor.png", assets);
//	Texture::loadTexture("res/textures/wall.png", assets);
//*/
//	//Sprite::loadSprite("res/sprites/guy.sprite", assets);
//
//
//
//	//assets.get<Texture>("res/textures/floor.png");
//	//assets.get<Texture>("res/textures/wall.png");
//
//	//assets.load<Sprite>("res/sprites/guy.sprite");
//	
//	//std::shared_ptr<Sprite> guy = std::make_shared<Sprite>( Sprite{ texData.getTexture("res/textures/guy.png"), Vec2(0.2f, 0.2f), "res/textures/guy.png" });
//	//_cursor = std::make_shared<Sprite>(Sprite { texData.getTexture("res/textures/cursor1.png"), Vec2(0.2f, 0.2f), "res/textures/cursor1.png" });
//	//std::shared_ptr<Sprite> floor = std::make_shared<Sprite>( Sprite { texData.getTexture("res/textures/floor.png"), Vec2(0.2f, 0.2f), "res/textures/floor.png" });
//	//std::shared_ptr<Sprite> wall = std::make_shared<Sprite>(Sprite{ texData.getTexture("res/textures/wall.png"), Vec2(0.2f, 0.2f), "res/textures/wall.png" });
//
//	//_assetData.spriteData.addSprite(_cursor);
//	//_assetData.spriteData.addSprite(floor);
//	//_assetData.spriteData.addSprite(wall);
//	//
//	//std::shared_ptr<GameState> gameState = std::make_shared<GameState>(*this, layer);
//	//std::shared_ptr<Actor> player = std::make_shared<Actor>(Vec2(0.4f, 0.2f), assets.get<Sprite>("res/sprites/guy.sprite"), std::make_shared<InputController>());
//	//gameState->addActor(player);
//	//gameState->setPlayer(player);
//	//gameState->addActor(new Actor(Vec2(-0.5f, -0.5f), snowman, new AIController(gameState)));
//	/*gameState->addActor(std::make_shared<Actor>(Vec2(0.5f, 0.7f), guy));
//	gameState->addActor(std::make_shared<Actor>(Vec2(0.3f, 0.7f), guy));
//	gameState->addActor(std::make_shared<Actor>(Vec2(0.82f, 0.74f), guy));
//	gameState->addActor(std::make_shared<Actor>(Vec2(0.2f, 0.23f), guy));
//	std::shared_ptr<Actor> a = std::make_shared<Actor>(Vec2(0.5f, 0.5f), guy, std::make_shared<AIController>(gameState));
//	a->setConversation(conv);
//	gameState->addActor(a);
//	*/
//	//_cursor = Renderable2D::createRenderable2D(cursorSprite, Vec4(), 0.5f, true);
//	
//	_states.push_back(std::make_unique<MenuState>());
//	_states.push_back(std::move(loadGameState("res/levels/testlevel.txt", *this, assets)));
//	_gameTimer.start();
//}
//
//Game::~Game()
//{
//	_states.clear();
//}
//
//
//void Game::update(float frameTime)
//{
///*	Game::frameTime = frameTime;
//	//_cursor->setPos(Vec4(mousePos.x, mousePos.y, 1, 1));
//
//	auto& state = _states[_curStateIndex];
//	State_Condition sCond = state->update(*this);
//	if (sCond == STATE_FINISHED)
//	{
//		++_curStateIndex;
//		if (_curStateIndex >= _states.size())
//		{
//			_curStateIndex = 0;
//		}
//	}
//	_gameTimer.update();*/
//}
//
//#include <sstream>
//#include <iomanip>
//
//void Game::render(Layer& layer)
//{
//	static Input& in = Input::instance();
//	static auto& win = layer.getWindow();
//	static int winHeight = win.getHeight();
//	
//	const auto& state = _states[_curStateIndex];
//	state->render(layer);
//	Vec2 mousePos = win.getScreenCoordsRatioCorrected(in.getMouseX(), winHeight - in.getMouseY());
//	Vec2 cursorWorldPos = state->getInContextPosition(win.getScreenCoords(in.getMouseX(), winHeight - in.getMouseY()));
//	//MSG(cursorWorldPos.toString());
//	//MSG(math::projectToCoordinates(1.0f, 1.0f, 3.0f, -1.0f, 1.0f));
//	//MSG(mousePos.toString());
//	//std::stringstream stream;
//	//stream << std::fixed << std::setprecision(2) << (float)_gameTimer.getElapsedInMillis() * 0.001f;
//	//layer.submitText(stream.str(), Vec2(0.75f, 0.45f), 0.2f);
//}
//
//void Game::pushState(std::unique_ptr<State> state)
//{
//	_states.push_back(std::move(state));
//}
//
//void Game::popState()
//{
//	_states.pop_back();
//}
//
