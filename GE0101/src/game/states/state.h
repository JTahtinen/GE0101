#pragma once
#include <memory>
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
	Screen													_screen;
	std::vector<std::shared_ptr<ScreenElement>>				_elements;
	std::string												_label;
public:
	State(Window& win, std::weak_ptr<Sprite> cursorSprite, const char* label);
	virtual ~State() {};
	virtual State_Condition update(Application& app) = 0;
	virtual void render(Layer& layer);
	virtual Vec2 getInContextPosition(const Vec2& screenPosition) const = 0;
	virtual void addScreenElement(std::shared_ptr<ScreenElement> element);
	virtual void clear();
};