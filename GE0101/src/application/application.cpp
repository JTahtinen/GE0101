#include "application.h"
#include "../input/input.h"
#include "../graphics/textbox.h"
#include "../util/log.h"
#include "../defs.h"
#include "../ui/slider.h"
#include "../util/timer.h"
#include "../graphics/screen.h"
#include "../graphics/button.h"
#include "../game/states/menustate.h"
#include "../game/states/gamestate.h"
#include "heaptracker.h"
#include <sstream>
#include <iomanip>
#include <memory>
#include "../datatypes/string.h"
//Log gameLog;
AssetManager g_assetManager;
HeapTracker g_heapTracker;

float Application::frametime;

static bool s_running;

static void buttonTest()
{
	MSG("Button pressed!");
}

/*void Application::loadGlobalData()
{
	BatchRenderer::init(_window);
	QuadRenderer::init(_window);
	TextRenderer::init(_window);
}

void Application::deleteGlobalData()
{
	BatchRenderer::quit();
	QuadRenderer::quit();
	TextRenderer::quit();
}
*/


Application::Application()
	: _window(1280, 720, "GE0101", false)
	, _layer(_window, g_assetManager.get<Font>("res/fonts/liberation_serif"))
{
	
	String testString = "Hello, there again! How are you?";
	testString.set("Hello, there again!");
//	MSG(testString.c_str());
	testString.print();

	_states.reserve(2);
	//loadGlobalData();
	//_layer = std::make_shared<Layer>(&_window);
	//_game = std::make_shared<Game>(_assetData);
	_states["menu"] = std::make_unique<Menu>(*this);
	_states["game"] = std::move(Game::loadGameState("res/levels/testlevel.txt", *this));
	_currentState = "menu";
	
}

Application::~Application()
{
	//deleteGlobalData();
	_states.clear();
	g_assetManager.clear();
}

void Application::run()
{
	/*std::vector<Vec2> points = { {0.0f, 0.1f}, {0.3f, 0.5f}, {0.4f, 0.6f}, {0.5f, 0.1f}, {1.0f, 0.9f}, {0.75f, 0.8f}, {0.9f, 1.3f}, {0.5f, 1.8f} };
	std::vector<Vec2> points2 = { {1.5f, 0.0f}, {1.5f, -0.5f}, {2.0f, -0.5f}, {2.0f, 0.0f} };
	Polygon testPoly(points);
	Polygon testPoly2(points2);*/

	s_running = true;
	Input& in = Input::instance();

	std::shared_ptr<Font> lsFont = g_assetManager.get<Font>("res/fonts/liberation_serif");
	std::shared_ptr<Font> arialFont = g_assetManager.get<Font>("res/fonts/arial");

	Layer gameLayer(_window, lsFont);
	Layer uiLayer(_window, lsFont);
	Layer cursorLayer(_window, lsFont);
	Layer* layers[3];

	layers[0] = &gameLayer;
	layers[1] = &uiLayer;
	layers[2] = &cursorLayer;
	//TextRenderable* engineInfo = TextRenderable::createTextRenderable("Lord Engine, v0.1", lsFont, Vec4(0.5f, -0.48f, 0, 1), 0.3f, true);
	TextBox textBox("FPS: ", 0.3f);
	textBox.setColor(Vec4(0.1f, 0.6f, 0.0f, 0.6f));

	int fps = 0;
	Vec2 fpsScreenPos(-0.9f, 0.45f);
	bool updateFPS = true;
	bool toggleFPS = true;
	
	Vec3 curWinColor(0.50f, 0.45f, 0.45f);
	Vec3 winColor = curWinColor;

	static int winHeight = _window.getHeight();
	const std::shared_ptr<const Sprite> cursor = g_assetManager.get<Sprite>("res/sprites/cursor.sprite");

	

	float frameTime = 0;
	unsigned int frames = 0;
	float runningTime = 0;

	Timer gameTimer;
	gameTimer.start();

	float enBoxScale = 0.4f;

	TextBox EngineBox("Lord Engine, v0.1", enBoxScale);
	EngineBox.addContent("(C) Jaakko Tahtinen");


	bool startNewGame = false;


	auto& menu = _states["menu"];

	std::shared_ptr<Frame> sliderCollection = std::make_shared<Frame>(Vec2(0.25f, 0), Vec2(0.5f, 0.5f));


	std::shared_ptr<Slider> red = std::make_shared<Slider>(0.0f, 1.0f, &winColor.x, "Red", Vec2(1.25f, 0.5f));
	std::shared_ptr<Slider> green = std::make_shared<Slider>(0.0f, 1.0f, &winColor.y, "Green", Vec2(1.35f, 0.5f));
	std::shared_ptr<Slider> blue = std::make_shared<Slider>(0.0f, 1.0f, &winColor.z, "Blue", Vec2(1.45f, 0.5f));

	sliderCollection->addChild(red);
	sliderCollection->addChild(green);
	sliderCollection->addChild(blue);

	// menu->addScreenElement(std::make_shared<Slider>(0.0f, 1.0f, &winColor.x, "Red", Vec2(1.60f, 0.5f)));
	// menu->addScreenElement(std::make_shared<Slider>(0.0f, 1.0f, &winColor.y, "Green", Vec2(1.70f, 0.5f)));
	// menu->addScreenElement(std::make_shared<Slider>(0.0f, 1.0f, &winColor.z, "Blue", Vec2(1.80f, 0.5f)));
	menu->addScreenElement(sliderCollection);
	menu->addScreenElement(std::make_shared<Button>("New Game", Vec2(0.75f, 0.55f), Vec2(0.5f, 0.1f), &startNewGame));
	menu->addScreenElement(std::make_shared<Button>("Exit", Vec2(0.75f, 0.25f), Vec2(0.5f, 0.1f), &s_running));
	bool gameExists = false;
	bool returnToGame = false;
	/*std::string totalAllocStr = "Total heap allocations: ";
	std::string freedAllocStr = "Freed heap allocations: ";
	std::string currentAllocStr = "Current heap allocations: ";
*/
	
	while (s_running)
	{
		_window.clear();
		in.update();

		if (startNewGame)
		{
			newGame();
			if (!gameExists)
			{
				menu->addScreenElement(std::make_shared<Button>("Return to game", Vec2(0.75f, 0.4f), Vec2(0.5f, 0.1f), &returnToGame));
				gameExists = true;
			}
			startNewGame = false;
		}

		if (returnToGame)
		{
			setCurrentState("game");
			returnToGame = false;
		}

		Vec2 mousePos = _window.getScreenCoordsRatioCorrected(in.getMouseX(), winHeight - in.getMouseY());
	/*	if (in.pollKeyboard(KEY_ESCAPE))
		{
			s_running = false;
		}
		*/
		if (in.pollKeyboard(KEY_F, KEYSTATE_TYPED))
		{
			toggleFPS = !toggleFPS;
		}

		if (in.pollKeyboard(KEY_P, KEYSTATE_TYPED))
		{
			_window.toggleFullScreen();
		}


		frameTime = (float)(gameTimer.getElapsedSinceLastUpdateInMillis() * 0.001f);

		for (auto& layer : layers)
		{
			layer->begin();
		}



		auto& state = _states[_currentState];
		ASSERT(state);
		State_Condition sCond = state->update(*this);
		_gameTimer.update();


		Application::frametime = frameTime;
		//_game.update(frameTime);
		gameTimer.update();
		runningTime += frameTime;
		if (updateFPS)
		{
			textBox.setContent("FPS: " + std::to_string(fps));
			updateFPS = false;
		}

		if (curWinColor != winColor)
		{
			_window.setClearColor(winColor.x, winColor.y, winColor.z);
			curWinColor = winColor;
		}
		state->render(gameLayer);
		textBox.render(uiLayer, fpsScreenPos);

		EngineBox.render(uiLayer, Vec2(0.2f, -0.52f));

	/*	uiLayer.submitPolygon(testPoly, Vec2(0, 0));
		uiLayer.submitPolygon(testPoly2, Vec2(0, 0));*/
		//	cursorLayer.submitSprite(cursor, Vec2(mousePos.x, mousePos.y - cursor->size.y), Vec3(0, 0, -1));
		
	/*	std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << g_heapTracker.getTotalAllocationsInMegaBytes(); 
		uiLayer.submitText(totalAllocStr + stream.str() + " MB" , Vec2(-0.95f, 0.3f), 0.2f);
		std::stringstream stream2;
		stream2 << std::fixed << std::setprecision(2) << g_heapTracker.getFreedAllocationsInMegaBytes();
		uiLayer.submitText(freedAllocStr + stream2.str() + " MB", Vec2(-0.95f, 0.25f), 0.2f);
		std::stringstream stream3;
		stream3 << std::fixed << std::setprecision(2) << g_heapTracker.getCurrentAllocationsInMegaBytes();
		uiLayer.submitText(currentAllocStr + stream3.str() + " MB", Vec2(-0.95f, 0.2f), 0.2f);*/
		
		for (auto& layer : layers)
		{
			layer->end();
			layer->flush();
		}
		
		++frames;
		if (runningTime >= 1.0f)
		{
			--runningTime;
			fps = frames;
			frames = 0;
			updateFPS = true;
			//MSG(totalAllocStr << g_heapTracker.getTotalAllocationsInMegaBytes() << " MB");
			//MSG(freedAllocStr << g_heapTracker.getFreedAllocationsInMegaBytes() << " MB");
			//MSG(currentAllocStr << g_heapTracker.getCurrentAllocationsInMegaBytes() << " MB\n");
		}
		_window.update();
	}
	//gameLog.writeToFile("log.txt");
}

void Application::setCurrentState(const std::string& state)
{
	_currentState = state;
}

void Application::newGame()
{
	_states["game"] = std::move(Game::loadGameState("res/levels/testlevel.txt", *this));
	_currentState = "game";
}