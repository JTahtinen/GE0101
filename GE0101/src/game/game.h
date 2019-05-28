#pragma once
#include "../graphics/window.h"
#include "map.h"
#include <vector>
#include "entity.h"
#include "actor.h"
#include "camera.h"
#include "assets/assetdata.h"
#include "gamedata.h"
#include "state.h"
#include "../graphics/renderers/renderer.h"

class Game
{
	std::vector<State*>		_stateStack;
	Renderer*				_renderer;
	AssetData				_assetData;
	Renderable2D*			_cursor;
public:
	static float frameTime;
public:
	Game(Renderer* renderer);
	~Game();

	void update(float frameTime);
	void pushState(State* state);
	void popState();
	const AssetData* getAssetData() const;
};