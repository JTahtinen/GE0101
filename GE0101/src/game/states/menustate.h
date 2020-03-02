#pragma once
#include "state.h"

class MenuState : public State
{
public:
	virtual State_Condition update(Game& game) override;
	virtual void render(Layer& layer) override;
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const override;
};