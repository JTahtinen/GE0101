#include "application.h"
#include <chrono>
#include <time.h>
#include "../input/input.h"
#include "../graphics/textbox.h"
#include "../util/log.h"

Log gameLog;

void loadGlobalData()
{
}

void deleteGlobalData()
{
}

Application::Application()
	: _renderer(1280, 720, "GE0101")
{
	loadGlobalData();
	_game = new Game(&_renderer);
	
}

Application::~Application()
{
	delete _game;
	_game = nullptr;
	deleteGlobalData();
}

void Application::run()
{


	bool running = true;

	Input& in = Input::instance();

	//float zoom = 1;
	float frameTime = 0;
	unsigned int frames = 0;
	clock_t lastTime = clock();
	float runningTime = 0;

	Font* arialFont = Font::loadFont("res/fonts/arial");
	Font* lsFont = Font::loadFont("res/fonts/liberation_serif");
	TextBox::setDefaultFont(arialFont);
	TextRenderable* engineInfo = TextRenderable::createTextRenderable("Lord Engine, v0.1", lsFont, Vec4(0.5f, -0.48f, 0, 1), 0.3f, true);
	TextBox textBox("FPS: ", 0.3f);
	textBox.setColor(Vec4(0.1f, 0.6f, 0.0f, 1.0f));
	textBox.setFont(lsFont);

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
	
		clock_t currentTime = clock();
		frameTime = (float)(currentTime - lastTime) / CLOCKS_PER_SEC;
		_game->update(frameTime);
		lastTime = currentTime;
		runningTime += frameTime;
		if (updateFPS)
		{
			textBox.setContent("FPS: " + std::to_string(fps));
			updateFPS = false;
		}
		if (toggleFPS)
		textBox.render(&_renderer, fpsScreenPos);


		_renderer.submit(engineInfo);
		_renderer.flush();
		
		++frames;
		if (runningTime >= 1.0f)
		{
			--runningTime;
			fps = frames;
			frames = 0;
			updateFPS = true;
		}
	}
	delete lsFont;
	//delete arialFont;
}