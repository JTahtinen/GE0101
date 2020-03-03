#include "screen.h"
#include "../input/input.h"

Screen::Screen(std::shared_ptr<const Sprite> cursorSprite)
	: _cursorSprite(cursorSprite)
	, _selectedElement(nullptr)
{
	_screenElements.reserve(500);
}

void Screen::update(const Window& win)
{
	static Input& in = Input::instance();
	_cursorPos = win.getScreenCoordsRatioCorrected(in.getMouseX(), win.getHeight() - in.getMouseY());
	
	if (!_selectedElement)
	{
		selectScreenElement(win);
		if (!_selectedElement)
		{
			return;
		}
	}
	
	Vec2 relativeCursorPos = _cursorPos - _selectedElement->getScreenPos();
	bool unSelectElement = false;
	if (_selectedElement->coversPoint(_cursorPos))
	{
		_selectedElement->onHover(relativeCursorPos);
	}
	else
	{
		unSelectElement = true;
	}
	if (in.pollMouse(MOUSESTATE_CLICKED))
	{
		_selectedElement->onClick(relativeCursorPos);
	}
	if (in.pollMouse(MOUSESTATE_CLICK_HELD))
	{
		_selectedElement->onClickHold(relativeCursorPos);
		unSelectElement = false;
	}
	if (in.pollMouse(MOUSESTATE_RELEASED))
	{
		_selectedElement->onRelease(relativeCursorPos);
		if (!_selectedElement->coversPoint(_cursorPos))
		{
			unSelectElement = true;
		}
	}
	if (unSelectElement)
	{
		_selectedElement->onExit(relativeCursorPos);
		_selectedElement = nullptr;
	}
}

void Screen::addScreenElement(ScreenElement* screenElement)
{
	if (screenElement)
	{
		_screenElements.emplace_back(screenElement);
	}
}

void Screen::selectScreenElement(const Window& win)
{
	for (auto& screenElement : _screenElements)
	{
		if (screenElement->coversPoint(_cursorPos))
		{
			_selectedElement = screenElement;
			return;
		}
	}
	_selectedElement = nullptr;
}