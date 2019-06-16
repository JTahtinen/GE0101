#pragma once
#include "../graphics/window.h"
#include "map.h"
#include <vector>
#include "entity/entity.h"
#include "entity/actor.h"
#include "camera.h"
#include "states/state.h"
#include "../graphics/layer.h"

class AssetManager;

class Game
{
	std::vector<std::shared_ptr<State>>			_stateStack;
	std::shared_ptr<Sprite>						_cursor;
public:
	static float frameTime;
public:
	Game(AssetManager& assets);
	~Game();

	void update(float frameTime);
	void render(Layer& layer);
	void pushState(std::shared_ptr<State> state);
	void popState();
	static std::shared_ptr<GameState> loadGameState(const std::string& filepath, Game& game, AssetManager& assets);
};