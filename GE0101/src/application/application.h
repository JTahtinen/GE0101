#pragma once
#include "../graphics/window.h"
#include "../game/game.h"
#include "../graphics/renderers/renderer.h"
#include <vector>
#include "../graphics/layer.h"
#include "appassetdata.h"

class Application
{
	std::shared_ptr<Layer>			_layer;
	std::shared_ptr<Game>			_game;
	Window							_window;
	AppAssetData					_assetData;
public:
	Application();
	~Application();
	void run();
private:
	void loadGlobalData();
	void deleteGlobalData();
};