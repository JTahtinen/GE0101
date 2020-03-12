#include "state.h"

State::State(Window& win, std::weak_ptr<Sprite> cursorSprite, const char* label)
	: _screen(cursorSprite, win)
	, _label(label)
{
	_elements.reserve(20);
	_screen.addFrame(FRAMETYPE_FULL, label);
}

void State::render(Layer& layer)
{
	_screen.update();
}

void State::addScreenElement(std::shared_ptr<ScreenElement> element)
{
	_elements.emplace_back(element);
	_screen.addScreenElement(_elements.back(), _label.c_str());
}

void State::clear()
{
	for (std::weak_ptr<ScreenElement> elem : _elements)
	{
		_screen.removeScreenElement(elem);
	}
	_elements.clear();
}