#pragma once
#include "../graphics/window.h"
#include "map.h"
#include <vector>
#include "entity/entity.h"
#include "entity/actor.h"
#include "camera.h"
#include "assets/assetdata.h"
#include "states/state.h"
#include "../graphics/layer.h"

class Game
{
	std::vector<State*>		_stateStack;
	Layer*					_layer;
	AssetData				_assetData;
	Sprite*					_cursor;
public:
	static float frameTime;
public:
	Game(Layer* layer);
	~Game();

	void update(float frameTime);
	void pushState(State* state);
	void popState();
	const AssetData* getAssetData() const;
};