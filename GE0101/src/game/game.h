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
	std::vector<std::shared_ptr<State>>			_stateStack;
	std::shared_ptr<Layer>						_layer;
	AssetData									_assetData;
	std::shared_ptr<Sprite>						_cursor;
public:
	static float frameTime;
public:
	Game(std::shared_ptr<Layer> layer);
	~Game();

	void update(float frameTime);
	void pushState(std::shared_ptr<State> state);
	void popState();
	const AssetData* getAssetData() const;
};