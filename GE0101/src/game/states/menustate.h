#pragma once
#include "state.h"

class Menu : public State
{
public:
	virtual State_Condition update(Application& app) override;
	virtual void render(Layer& layer) override;
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const override;
};