#include "application.h"
#include <chrono>
#include <time.h>
#include "../input/input.h"
#include "../graphics/textbox.h"
#include "../util/log.h"
#include "../graphics/renderers/simplerenderer.h"
#include "../defs.h"

Log gameLog;

void Application::loadGlobalData()
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

Application::Application()
	: _window(1280, 720, "GE0101")
{
	loadGlobalData();
	_layer = std::make_shared<Layer>(&_window);
	_game = std::make_shared<Game>(_layer);
	
}

Application::~Application()
{
	deleteGlobalData();
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

	std::shared_ptr<Font> lsFont = Font::loadFont("res/fonts/liberation_serif");
	std::shared_ptr<Font> arialFont = Font::loadFont("res/fonts/arial");
	
	_assetData.fontData.addElement(lsFont, "liberation_serif");
	_assetData.fontData.addElement(arialFont, "arial");
	//TextRenderable* engineInfo = TextRenderable::createTextRenderable("Lord Engine, v0.1", lsFont, Vec4(0.5f, -0.48f, 0, 1), 0.3f, true);
	TextBox::setDefaultFont(_assetData.fontData.getElement("liberation_serif"));
	TextBox textBox("FPS: ", 0.3f);
	textBox.setColor(Vec4(0.1f, 0.6f, 0.0f, 0.6f));
	textBox.setFont(arialFont);

	int fps = 0;
	Vec2 fpsScreenPos(-0.9f, 0.45f);
	Vec2 mouse;
	bool updateFPS = true;
	bool toggleFPS = true;
	while (running)
	{
		in.update();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}

		if (in.poll(KEY_F, KEYSTATE_TYPED))
		{
			toggleFPS = !toggleFPS;
		}
	
		auto currentTime = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(currentTime - lastTime);
		frameTime = (float)(duration.count() / 1000.0f);
		_layer->begin();
		
		_game->update(frameTime);
		lastTime = currentTime;
		runningTime += frameTime;
		if (updateFPS)
		{
			textBox.setContent("FPS: " + std::to_string(fps));
			updateFPS = false;
		}
		//if (toggleFPS)
		//textBox.render(_renderer, fpsScreenPos);
		textBox.render(*_layer, fpsScreenPos);

		//_layer.submitText(engineInfo);
		_layer->submitText("Lord Engine, v0.1", Vec2(0.4f, -0.47f), 0.4f, lsFont);
		
		//_layer->submitText("Lord Engine, v0.1", Vec2(0.0f, 0.0f), 0.4f, lsFont);
		_layer->end();
		_layer->flush();

		
		++frames;
		if (runningTime >= 1.0f)
		{
			--runningTime;
			fps = frames;
			frames = 0;
			updateFPS = true;
		}
	}
	gameLog.writeToFile("log.txt");
}