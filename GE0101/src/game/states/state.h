#pragma once
#include "../../graphics/screen.h"

class Application;
class Layer;
class Vec2;
class Window;

enum State_Type
{
	STATE_GAME,
	STATE_CONVERSATION
};

enum State_Condition
{
	STATE_RUNNING,
	STATE_FINISHED
};

class State
{
protected:
	Screen						_screen;
public:
	State(Window& win, std::weak_ptr<Sprite> cursorSprite);
	virtual ~State() {};
	virtual State_Condition update(Application& app) = 0;
	virtual void render(Layer& layer);
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const = 0;
	void addScreenElement(std::unique_ptr<ScreenElement> element, const std::string& label);
};