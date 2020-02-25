#pragma once
#include "../graphics/window.h"
#include "../game/game.h"
#include "../graphics/renderers/renderer.h"
#include <vector>
#include "../graphics/layer.h"
#include "assetmanager.h"

class Application
{
	Window							_window;
	Layer							_layer;
	AssetManager					_assetData;
	Game							_game;
public:
	Application();
	~Application();
	void run();
private:
//	void loadGlobalData();
//	void deleteGlobalData();
};