#pragma once
#include "state.h"
#include "../../graphics/button.h"
#include <vector>

class Application;

class Menu : public State
{
	//std::vector<Button>				_buttons;
public:
	Menu(Application& app);
	~Menu();
	virtual State_Condition update(Application& app) override;
	virtual void render(Layer& layer) override;
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const override;
	void clear();
};