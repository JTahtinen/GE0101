#include "application.h"
#include "../math/math.h"
#include <SDL2/SDL.h>
#include "../input/input.h"
#include "../util/log.h"
#include "../game/scenegraph.h"
#include "../util/file.h"
#include "SDL2/SDL_image.h"
#include "../graphics/buffers/vertexarray.h"
#include "../graphics/buffers/indexbuffer.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/renderers/simple2drenderer.h"

Log gameLog;

Sprite defaultSprite;
Tile defTile;
Texture* snowman;
VertexArray* vao;
BufferLayout tileLayout;
BufferLayout texCoordLayout;
Buffer* texCoordBuffer;
Buffer* tileVertices;
IndexBuffer* tileIndices;

void loadGlobalData()
{
	vao = new VertexArray();
	texCoordBuffer = new Buffer();
	tileVertices = new Buffer();
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



	tileVertices->push(&tileVertData[0], sizeof(tileVertData));
	tileIndices->push(&tileIndexData[0], 6);
	vao->push(tileVertices, tileLayout);

	texCoordBuffer->push(&texCoords[0], 4 * sizeof(Vec2));
	texCoordLayout.push<float>(2);
	vao->push(texCoordBuffer, texCoordLayout);
	Buffer* tileVertices = new Buffer();
	defaultSprite.vbo = tileVertices;
	defaultSprite.indices = tileIndices;


	snowman = new Texture("res/textures/IMG_2086.png");
	snowman->bind(0);

	defTile.texture = snowman;
	defTile.barrier = false;
	defaultSprite.vbo->push(&tileVertices[0], 4 * sizeof(Vec2));



}

void deleteGlobalData()
{
	delete texCoordBuffer;
	delete snowman;
	delete vao;
	delete tileVertices;
	delete tileIndices;
}

Application::Application()
	: _window(1280, 720, "GE0101")
{
	loadGlobalData();
	_renderer = new Simple2DRenderer();
	_game = new Game(_renderer);
}

Application::~Application()
{
	deleteGlobalData();
	delete _renderer;
	_renderer = nullptr;
}

void Application::run()
{

	const Camera& camera = _game->getCamera();

	//Buffer vbo;
	Buffer colorBuffer;
	BufferLayout layout;
	
	
	//Shaders

	Shader shader("res/shaders/basic");
	shader.bind();

	shader.setUniform1i("u_Texture", 0);
	shader.setUniform4f("u_Color", 1.0f, 0, 1.0f, 1.0f);
	shader.setUniform1f("u_Zoom", camera.getZoom());

	_renderer->setShader(&shader);

	defaultSprite.texture = snowman;
	defaultSprite.name = "snowman";
	
	
	vao->push(defaultSprite.vbo, tileLayout);



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
	shader.setUniform1f("u_ScrRatio", (float)_window.getWidth() / (float)_window.getHeight());
	MSG("Screen Ratio: " << (float)_window.getWidth() / (float)_window.getHeight());
	bool running = true;
	Vec2 pos(10, 10);

	Input& in = Input::instance();

	float r = 0;
	int dir = 1;
	float zoom = 1;
	bool updateZoom = false;
	while (running)
	{
		if (r <= 0)
		{
			dir = 1;
		}
		else if (r >= 0.6f)
		{
			dir = -1;
		}

		r += (float)dir * 0.001f;

		shader.setUniform4f("u_Color", r, 0, 0, 1.0f);


		in.update();
		if (in.poll(KEY_ESCAPE))
		{
			running = false;
		}


		shader.setUniform1f("u_Zoom", camera.getZoom());
		updateZoom = false;
		
		_window.clear();
		_game->update();
		_renderer->flush();
	//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);
		_window.update();
	}

}