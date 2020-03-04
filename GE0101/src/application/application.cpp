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

//Log gameLog;
AssetManager g_assetManager;

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

static void exit()
{
	s_running = false;
}

Application::Application()
	: _window(1280, 720, "GE0101", false)
	, _layer(_window, g_assetManager.get<Font>("res/fonts/liberation_serif"))
	, _exitButton("Exit", Vec2(-0.25f, -0.25f), Vec2(0.5f, 0.1f), &exit)
{
	_states.reserve(2);
	//loadGlobalData();
	//_layer = std::make_shared<Layer>(&_window);
	//_game = std::make_shared<Game>(_assetData);
	_states.push_back(std::make_unique<MenuState>());
	_states.push_back(std::move(GameState::loadGameState("res/levels/testlevel.txt", *this)));
}

Application::~Application()
{
	//deleteGlobalData();
	_states.clear();
	g_assetManager.clear();
}

void Application::run()
{
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
	Slider red(0.0f, 1.0f, &winColor.x, "Red", Vec2(0.60f, 0.0f));
	Slider green(0.0f, 1.0f, &winColor.y, "Green", Vec2(0.70f, 0.0f));
	Slider blue(0.0f, 1.0f, &winColor.z, "Blue", Vec2(0.80f, 0.0f));

	static int winHeight = _window.getHeight();
	const std::shared_ptr<const Sprite> cursor = g_assetManager.get<Sprite>("res/sprites/cursor.sprite");

	bool slidersVisible = false;


	float frameTime = 0;
	unsigned int frames = 0;
	float runningTime = 0;

	Timer gameTimer;
	gameTimer.start();

	float enBoxScale = 0.4f;

	TextBox EngineBox("Lord Engine, v0.1", enBoxScale);
	EngineBox.addContent("(C) Jaakko Tahtinen");

	Button newGameButton("New Game", Vec2(-0.25f, 0.05f), Vec2(0.5f, 0.1f), &buttonTest);

	Screen screen(cursor, _window);
	screen.addScreenElement(&red);
	screen.addScreenElement(&green);
	screen.addScreenElement(&blue);
	screen.addScreenElement(&newGameButton);
	screen.addScreenElement(&_exitButton);


	while (s_running)
	{
		_window.clear();
		in.update();

		Vec2 mousePos = _window.getScreenCoordsRatioCorrected(in.getMouseX(), winHeight - in.getMouseY());
		if (in.pollKeyboard(KEY_ESCAPE))
		{
			s_running = false;
		}

		if (in.pollKeyboard(KEY_F, KEYSTATE_TYPED))
		{
			toggleFPS = !toggleFPS;
		}

		if (in.pollKeyboard(KEY_U))
		{
			enBoxScale *= 1.01f;
			EngineBox.setScale(enBoxScale);
		}
		if (in.pollKeyboard(KEY_J))
		{
			enBoxScale *= 0.99f;
			EngineBox.setScale(enBoxScale);
		}

		if (in.pollKeyboard(KEY_P, KEYSTATE_TYPED))
		{
			_window.toggleFullScreen();
		}

		if (in.pollKeyboard(KEY_M, KEYSTATE_TYPED))
		{
			slidersVisible = !slidersVisible;
		}

		frameTime = (float)(gameTimer.getElapsedSinceLastUpdateInMillis() * 0.001f);

		for (auto& layer : layers)
		{
			layer->begin();
		}



		auto& state = _states[_curStateIndex];
		State_Condition sCond = state->update(*this);
		if (sCond == STATE_FINISHED)
		{
			++_curStateIndex;
			if (_curStateIndex >= _states.size())
			{
				_curStateIndex = 0;
			}
		}
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
		
		/*if (slidersVisible)
		{
			red.render(uiLayer);
			green.render(uiLayer);
			blue.render(uiLayer);
		}*/
		//uiLayer.submitText("Lord Engine, v0.1", Vec2(0.4f, -0.52f), 0.4f, lsFont);
		EngineBox.render(uiLayer, Vec2(0.2f, -0.52f));
		//	cursorLayer.submitSprite(cursor, Vec2(mousePos.x, mousePos.y - cursor->size.y), Vec3(0, 0, -1));

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
		}
		screen.update(_window);
		_window.update();
	}
	//gameLog.writeToFile("log.txt");
}