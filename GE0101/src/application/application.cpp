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
	deleteGlobalData();
}

void Application::run()
{

//	const Camera& camera = _game->getCamera();


	bool running = true;

	Input& in = Input::instance();

	//float zoom = 1;
	float frameTime = 0;
	unsigned int frames = 0;
	clock_t lastTime = clock();
	float runningTime = 0;

	Font* font = Font::loadFont("res/fonts/liberation_serif");
	TextBox::setFont(font);
	//TextRenderable* text = TextRenderable::createTextRenderable("Lord Engine, v0.1", font, Vec2(0.35, -0.45f), 0.4f, true);
	TextRenderable* text = TextRenderable::createTextRenderable("Lord Engine, v0.1", font, Vec2(0.0f, -0.4f), 0.4f, true);
	TextBox textBox("FPS: ");

	int fps = 0;
	Vec2 fpsScreenPos(-0.9f, 0.35f);
	Vec2 mouse;
	bool updateFPS = true;
	while (running)
	{
		//mouse = _window.getScreenCoordsRatioCorrected(in.getMouseX(), _window.getHeight() - in.getMouseY());

		in.update();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
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
		textBox.render(&_renderer, fpsScreenPos);


		_renderer.submit(text);
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
	delete font;
}