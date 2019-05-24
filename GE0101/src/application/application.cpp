#include "application.h"
#include <chrono>
#include <time.h>
#include "../input/input.h"
#include "../graphics/textbox.h"
#include "../util/log.h"

Log gameLog;

Shader* basicShader;


void loadGlobalData()
{


	/*Vec2 texCoords[] = {
		Vec2(0, 1),
		Vec2(0, 0),
		Vec2(1, 0),
		Vec2(1, 1)
	};
*/


	initRenderables();
}

void deleteGlobalData()
{
	delete basicShader;

	destroyRenderables();
}

Application::Application()
	: _window(1280, 720, "GE0101")
{
	loadGlobalData();

	_game = new Game(&_renderer);

	basicShader = new Shader("res/shaders/basic");
	basicShader->bind();

	basicShader->setUniform1i("u_Texture", 0);
	basicShader->setUniform4f("u_Color", 0.0f, 0, 1.0f, 0.0f);
	basicShader->setUniform1f("u_ScrRatio", (float)_window.getWidth() / (float)_window.getHeight());
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
	
	//TextRenderable* text = TextRenderable::createTextRenderable("Lord Engine, v0.1", font, Vec2(0.35, -0.45f), 0.4f, true);
	TextRenderable* text = TextRenderable::createTextRenderable("Lord Engine, v0.1", font, Vec2(0.0f, 0.0f), 0.4f, true);
	TextBox textBox("FPS: ", font);

	int fps = 0;
	Vec2 fpsScreenPos(-1.5f, 0.9f);
	Vec2 mouse;
	bool updateFPS = true;
	while (running)
	{
		mouse = _window.getScreenCoordsRatioCorrected(in.getMouseX(), _window.getHeight() - in.getMouseY());

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
		textBox.render(&_renderer, Vec2(-0.95f, 0.2f));


		_renderer.submit(text);

		_window.clear();
		_renderer.flush();
		_window.update();

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