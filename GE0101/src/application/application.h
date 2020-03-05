#pragma once
#include "../graphics/window.h"
#include "../graphics/renderers/renderer.h"
#include "../graphics/button.h"
#include <vector>
#include "../graphics/layer.h"
#include "assetmanager.h"
#include "../game/states/state.h"
#include "../game/states/gamestate.h"
#include "../game/states/menustate.h"
#include "../util/timer.h"
#include <unordered_map>
#include <string>

class Application
{
//	AssetManager					_assetData;
	
	Window																_window;
	std::unordered_map<std::string, std::unique_ptr<State>>				_states;
//std::vector<std::pair<std::unique_ptr<State>, std::string>>			_states;
	std::string															_currentState;
	Timer																_gameTimer;
	Layer																_layer;
	//Game																_game;
public:
	static float														frametime;

public:
	Application();
	~Application();
	void run();
	void setCurrentState(const std::string& state);
	Window& getWindow() { return _window; }
private:
	void newGame();
//	void loadGlobalData();
//	void deleteGlobalData();
};