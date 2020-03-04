#pragma once
#include "../graphics/window.h"
#include "../graphics/renderers/renderer.h"
#include "../graphics/button.h"
#include <vector>
#include "../graphics/layer.h"
#include "assetmanager.h"
#include "../game/states/state.h"
#include "../util/timer.h"

class Application
{
//	AssetManager					_assetData;
	std::vector<std::unique_ptr<State>>			_states;
	unsigned int								_curStateIndex;
	Timer										_gameTimer;
	Window										_window;
	Layer										_layer;
	//Game										_game;
	Button										_exitButton;
public:
	static float								frametime;

public:
	Application();
	~Application();
	void run();
private:
//	void loadGlobalData();
//	void deleteGlobalData();
};