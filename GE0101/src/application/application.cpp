#include "application.h"
#include <chrono>
#include <time.h>
#include "../input/input.h"
#include "../graphics/textbox.h"
#include "../util/log.h"
#include "../defs.h"
#include "../ui/slider.h"

//Log gameLog;

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
	: _window(1280, 720, "GE0101")
	, _layer(_window, _assetData.get<Font>("res/fonts/liberation_serif"))
	, _game(_assetData)
{
	//loadGlobalData();
	//_layer = std::make_shared<Layer>(&_window);
	//_game = std::make_shared<Game>(_assetData);
	
}

Application::~Application()
{
	//deleteGlobalData();
}

void Application::run()
{
	using namespace std::chrono;

	bool running = true;

	Input& in = Input::instance();



	//float zoom = 1;
	float frameTime = 0;
	unsigned int frames = 0;
	auto lastTime = high_resolution_clock::now();
	float runningTime = 0;


	std::shared_ptr<Font> lsFont = _assetData.get<Font>("res/fonts/liberation_serif");
	std::shared_ptr<Font> arialFont = _assetData.get<Font>("res/fonts/arial");

	Layer gameLayer(_window, lsFont);
	Layer uiLayer(_window, lsFont);
	Layer cursorLayer(_window, lsFont);
	Layer* layers[3];

	layers[0] = &gameLayer;
	layers[1] = &uiLayer;
	layers[2] = &cursorLayer;
	//TextRenderable* engineInfo = TextRenderable::createTextRenderable("Lord Engine, v0.1", lsFont, Vec4(0.5f, -0.48f, 0, 1), 0.3f, true);
	TextBox::setDefaultFont(lsFont);
	TextBox textBox("FPS: ", 0.3f);
	textBox.setColor(Vec4(0.1f, 0.6f, 0.0f, 0.6f));
	textBox.setFont(arialFont);

	int fps = 0;
	Vec2 fpsScreenPos(-0.9f, 0.45f);
	Vec2 mouse;
	bool updateFPS = true;
	bool toggleFPS = true;
	
	Vec3 curWinColor(0.50f, 0.45f, 0.45f);
	Vec3 winColor = curWinColor;
	Slider red(0.0f, 1.0f, &winColor.x, "Red");
	Slider green(0.0f, 1.0f, &winColor.y, "Green");
	Slider blue(0.0f, 1.0f, &winColor.z, "Blue");
	
	static int winHeight = _window.getHeight();
	const auto& cursor = _assetData.get<Sprite>("res/sprites/cursor.sprite");

	while (running)
	{
		_window.clear();
		in.update();

		Vec2 mousePos = _window.getScreenCoordsRatioCorrected(in.getMouseX(), winHeight - in.getMouseY());
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}

		if (in.poll(KEY_F, KEYSTATE_TYPED))
		{
			toggleFPS = !toggleFPS;
		}

		if (in.poll(KEY_U))
		{
			red.slideByAbs(0.01f);
		}
		
		if (in.poll(KEY_J))
		{
			red.slideByAbs(-0.01f);
		}

		if (in.poll(KEY_I))
		{
			green.slideByAbs(0.01f);
		}

		if (in.poll(KEY_K))
		{
			green.slideByAbs(-0.01f);
		}

		if (in.poll(KEY_O))
		{
			blue.slideByAbs(0.01f);
		}

		if (in.poll(KEY_L))
		{
			blue.slideByAbs(-0.01f);
		}
	
		if (in.poll(KEY_X, KEYSTATE_TYPED))
		{
			red.toggleLabel();
			green.toggleLabel();
			blue.toggleLabel();
		}

		auto currentTime = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(currentTime - lastTime);
		frameTime = (float)(duration.count() / 1000.0f);
		//_layer.begin();
		for (auto& layer : layers)
		{
			layer->begin();
		}

		_game.update(frameTime);
		lastTime = currentTime;
		runningTime += frameTime;
		if (updateFPS)
		{
			textBox.setContent("FPS: " + std::to_string(fps));
			updateFPS = false;
		}
		//if (toggleFPS)
		//textBox.render(_renderer, fpsScreenPos);
		if (curWinColor != winColor)
		{
			_window.setClearColor(winColor.x, winColor.y, winColor.z);
			curWinColor = winColor;
		}
		_game.render(gameLayer);
		textBox.render(uiLayer, fpsScreenPos);

		red.render(uiLayer, Vec2(0.60f, 0.2f));
		green.render(uiLayer, Vec2(0.70f, 0.2f));
		blue.render(uiLayer, Vec2(0.80f, 0.2f));

		//_layer.submitText(engineInfo);
		uiLayer.submitText("Lord Engine, v0.1", Vec2(0.4f, -0.52f), 0.4f, lsFont);
		//uiLayer.submitText("Lord Engine, v0.1", Vec2(0.0f, 0.0f), 0.4f, lsFont);
		cursorLayer.submitSprite(cursor, mousePos, Vec3(0, 0, -1));

		//_layer->submitText("Lord Engine, v0.1", Vec2(0.0f, 0.0f), 0.4f, lsFont);
		//_layer.end();
		//_layer.flush();
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
		_window.update();
	}
	_assetData.clear();
	//gameLog.writeToFile("log.txt");
}