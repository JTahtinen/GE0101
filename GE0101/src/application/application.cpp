#include "application.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <chrono>
#include <time.h>
#include "../math/math.h"
#include "../input/input.h"
#include "../util/log.h"
#include "../game/scenegraph.h"
#include "../util/file.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/textbox.h"

Log gameLog;

Sprite defaultSprite;
Tile defTile;
Texture* snowman;
VertexArray* vao;
BufferLayout tileLayout;
BufferLayout texCoordLayout;
Buffer* texCoordBuffer;
VertexArray* tileVertices;
IndexBuffer* tileIndices;
Shader* basicShader;


void loadGlobalData()
{

	basicShader = new Shader("res/shaders/basic");

	texCoordBuffer = new Buffer();
	tileVertices = new VertexArray();
	tileIndices = new IndexBuffer();
	tileLayout.push<float>(2);


	Vec2 texCoords[] = {
		Vec2(0, 1),
		Vec2(0, 0),
		Vec2(1, 0),
		Vec2(1, 1)
	};

	Vec2 tileVertData[] = { Vec2(-0.1f, -0.1f),
						Vec2(-0.1f,  0.1f),
						Vec2(0.1f,  0.1f),
						Vec2(0.1f, -0.1f) };
	unsigned int tileIndexData[] = {
		0, 1, 2, 2, 3, 0
	};


	Buffer* tileVertexBuffer = new Buffer();
	tileVertexBuffer->push(&tileVertData[0], 4 * sizeof(Vec2));
	tileIndices->push(&tileIndexData[0], 6);
	tileVertices->push(tileVertexBuffer, tileLayout);

	texCoordBuffer->push(&texCoords[0], 4 * sizeof(Vec2));
	texCoordLayout.push<float>(2);
	tileVertices->push(texCoordBuffer, texCoordLayout);
	tileVertices->push(tileVertexBuffer, tileLayout);
	vao = tileVertices;
	defaultSprite.vao = vao;
	defaultSprite.indices = tileIndices;


	snowman = new Texture("res/textures/IMG_2086.png");
	snowman->bind(0);

	defTile.texture = snowman;
	defTile.barrier = false;

	

	initRenderables();
	basicShader->bind();

	basicShader->setUniform1i("u_Texture", 0);
	basicShader->setUniform4f("u_Color", 1.0f, 0, 1.0f, 1.0f);

	defaultSprite.texture = snowman;
	defaultSprite.name = "snowman";
}

void deleteGlobalData()
{
	delete basicShader;
	delete texCoordBuffer;
	delete snowman;
	delete tileVertices;
	delete tileIndices;

	destroyRenderables();
}

Application::Application()
	: _window(1280, 720, "GE0101")
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

	const Camera& camera = _game->getCamera();

	//Buffer vbo;
	Buffer colorBuffer;
	BufferLayout layout;
	
	
	//Shaders

	
	

	std::vector<Vec4> colors;
	colors.reserve(4);

	colors.push_back(Vec4(1.0f, 0, 0, 1.0f));
	colors.push_back(Vec4(0, 1.0f, 0, 1.0f));
	colors.push_back(Vec4(0, 0, 1.0f, 1.0f));
	colors.push_back(Vec4(1.0f, 1.0f, 0, 1.0f));


	colorBuffer.push(&colors[0], colors.size() * sizeof(Vec4));
	BufferLayout colorLayout;
	colorLayout.push<float>(4);
	vao->push(&colorBuffer, colorLayout);
	basicShader->setUniform1f("u_ScrRatio", (float)_window.getWidth() / (float)_window.getHeight());
	bool running = true;

	Input& in = Input::instance();

	float r = 0;
	int dir = 1;
	float zoom = 1;
	float frameTime = 0;
	unsigned int frames = 0;
	clock_t lastTime = clock();
	float runningTime = 0;
	bool menu = false;

	Font* font = Font::loadFont("res/fonts/liberation_serif");
	
	TextRenderable* text = TextRenderable::createTextRenderable("Lord Engine, v0.1", font, Vec2(0.35, -0.45f), 0.4f, true);

	TextBox textBox("FPS: ", font);

	Texture crosshairTex("res/textures/cursor.png");
	Sprite crosshair;
	crosshair.vao = tileVertices;
	crosshair.indices = tileIndices;
	crosshair.texture = &crosshairTex;
	crosshair.name = "Crosshair";


	int fps = 0;
	Vec2 fpsScreenPos(-1.5f, 0.9f);
	Vec2 mouse;
	bool updateFPS = true;
	while (running)
	{
		//mouse = getWorldCoordsFromScreenPos(in.getMouseX(), 720 - in.getMouseY());
		mouse = _window.getScreenCoordsRatioCorrected(in.getMouseX(), _window.getHeight() - in.getMouseY());
	//	mouse.print();
		basicShader->bind();
		if (r < 0)
		{
			dir = 1;
		}
		else if (r >= 1.0f)
		{
			dir = -1;
		}

		r += (float)dir * frameTime;

		basicShader->setUniform4f("u_Color", 0.0f, 0.2f * r, 0.3f * r, 1.0f);

		in.update();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}
		if (in.poll(KEY_M, KEYSTATE_TYPED))
		{
			menu = !menu;
		}


		
		
		clock_t currentTime = clock();
		frameTime = (float)(currentTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = currentTime;
		_game->update(frameTime);
		runningTime += frameTime;
		//textRenderer.submit("FPS: " + std::to_string(fps), fpsScreenPos);
		if (updateFPS)
		{
			textBox.setContent("FPS: " + std::to_string(fps));
			updateFPS = false;
		}
		textBox.render(&_renderer, Vec2(-0.95f, 0.2f));
		_renderer.submit(text);
		if (menu)
		{
			QuadRenderable* bg = QuadRenderable::createQuadRenderable(Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), Vec4(0.2f, 0.2f, 0.8f, 1.0f));
			QuadRenderable* fg = QuadRenderable::createQuadRenderable(Vec2(0.1f, 0.1f), Vec2(0.8f, 0.8f), Vec4(0.7f, 0.6f, 0, 1.0f));
			bg->addChild(fg);

			_renderer.submit(bg);
		}

		Renderable2D* crosshairRenderable = Renderable2D::createRenderable2D(&crosshair, mouse, 1.0f);
		_renderer.submit(crosshairRenderable);
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