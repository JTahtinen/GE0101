//#pragma once
//#include "../graphics/window.h"
//#include "map.h"
//#include <vector>
//#include "entity/entity.h"
//#include "entity/actor.h"
//#include "camera.h"
//#include "states/state.h"
//#include "../graphics/layer.h"
//#include "../util/timer.h"
//
//class AssetManager;
//
//class Game
//{
//	std::vector<std::unique_ptr<State>>			_states;
//	unsigned int								_curStateIndex;
//	Timer										_gameTimer;
//public:
//	static float frameTime;
//public:
//	Game(AssetManager& assets);
//	~Game();
//
//	void update(float frameTime);
//	void render(Layer& layer);
//	void pushState(std::unique_ptr<State> state);
//	void popState();
//	static std::unique_ptr<GameState> loadGameState(const std::string& filepath, Game& game, AssetManager& assets);
//};