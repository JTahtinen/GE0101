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
#include "../graphics/renderers/simple2drenderer.h"
#include "../graphics/renderers/quadrenderer.h"
#include "../graphics/renderers/textrenderer.h"

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

void loadGlobalData()
{
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



}

void deleteGlobalData()
{
	delete texCoordBuffer;
	delete snowman;
	delete tileVertices;
	delete tileIndices;
}

Application::Application()
	: _window(1280, 720, "GE0101")
{
	loadGlobalData();
	_renderer2D = new Simple2DRenderer();
	_quadRenderer = new QuadRenderer();
	_renderers.push_back(_renderer2D);
	_renderers.push_back(_quadRenderer);

	_game = new Game(_renderer2D);
}

Application::~Application()
{
	deleteGlobalData();
	for (auto& renderer : _renderers)
	{
		delete renderer;
	}
	_renderers.empty();
}

void Application::run()
{

	const Camera& camera = _game->getCamera();

	//Buffer vbo;
	Buffer colorBuffer;
	BufferLayout layout;
	
	
	//Shaders

	Shader* shader = new Shader("res/shaders/basic");

	shader->bind();

	shader->setUniform1i("u_Texture", 0);
	shader->setUniform4f("u_Color", 1.0f, 0, 1.0f, 1.0f);
	shader->setUniform1f("u_Zoom", camera.getZoom());

	_renderer2D->setShader(shader);

	defaultSprite.texture = snowman;
	defaultSprite.name = "snowman";
	
	
	//vao->push(defaultSprite.vao, tileLayout);



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
	shader->setUniform1f("u_ScrRatio", (float)_window.getWidth() / (float)_window.getHeight());
	bool running = true;

	Input& in = Input::instance();

	float r = 0;
	int dir = 1;
	float zoom = 1;
	bool updateZoom = false;
	float frameTime = 0;
	unsigned int frames = 0;
	clock_t lastTime = clock();
	float runningTime = 0;
	bool menu = false;
	QuadRenderable bg = { Vec2(-0.0, 0.0), Vec2(1.0f, 1.0f), Vec4(0.2f, 0.2f, 0.8f, 1) };
	QuadRenderable fg = { Vec2(0, 0), Vec2(0.8f, 0.8f), Vec4(0.7f, 0.6f, 0, 1) };
	
	Font* font = Font::loadFont("res/fonts/arial");
	TextRenderer textRenderer(font);

	while (running)
	{
		shader->bind();
		if (r < 0)
		{
			dir = 1;
		}
		else if (r >= 1.0f)
		{
			dir = -1;
		}

		r += (float)dir * frameTime;

		shader->setUniform4f("u_Color", 0.0f, 0.2f * r, 0.3f * r, 1.0f);


		in.update();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}
		if (in.poll(KEY_M, KEYSTATE_TYPED))
		{
			menu = !menu;
		}

		if (menu)
		{
			_quadRenderer->submit(bg.pos, bg.dimensions, bg.color);
			_quadRenderer->submit(fg.pos, fg.dimensions, fg.color);
		}

		shader->setUniform1f("u_Zoom", camera.getZoom());
		updateZoom = false;
		
		clock_t currentTime = clock();
		frameTime = (float)(currentTime - lastTime) / CLOCKS_PER_SEC;
		lastTime = currentTime;
		_game->update(frameTime);
		runningTime += frameTime;

		_window.clear();

		textRenderer.submit("Hello There, honeypie", Vec2(-1.0f, 0));

		for (auto& renderer : _renderers)
		{
			renderer->flush();
		}

		textRenderer.flush();

		_window.update();

		++frames;
		if (runningTime >= 1.0f)
		{
			--runningTime;
			//MSG("FPS: " << frames);
			std::string title = "GE0101 | FPS: ";
			title.append(std::to_string(frames));
			_window.setTitle(title.c_str());
			frames = 0;
		}
	}

}