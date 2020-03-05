#include "state.h"

State::State(Window& win, std::weak_ptr<Sprite> cursorSprite)
	: _screen(cursorSprite, win)
{

}

void State::render(Layer& layer)
{
	_screen.update();
}

void State::addScreenElement(std::unique_ptr<ScreenElement> element, const std::string& label)
{
	_screen.addScreenElement(std::move(element), label);
}