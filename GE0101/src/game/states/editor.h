#pragma once
#include "state.h"

class Editor : public State
{
public:
	Editor(Window& win, std::weak_ptr<Sprite> cursorSprite);
	~Editor();
	virtual State_Condition update(Application& app) override;
	virtual void render(Layer& layer) override;
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const override;
};