#include  "menustate.h"
#include "../../input/input.h"
#include "../../graphics/layer.h"
#include "../../application/application.h"
#include "../../ui/slider.h"

Menu::Menu(Application& app)
	: State(app.getWindow(), g_assetManager.get<Sprite>("res/sprites/cursor.sprite"))
{
	
}

Menu::~Menu()
{
	clear();
}

State_Condition Menu::update(Application& app)
{
	return STATE_RUNNING;
}

void Menu::render(Layer& layer)
{
	State::render(layer);
}

Vec2 Menu::getInContextPosition(const Vec2& screenPosition) const
{
	return screenPosition;
}


void Menu::clear()
{
	//_buttons.clear();
}