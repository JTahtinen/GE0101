#include "screen.h"
#include "../input/input.h"
#include "../defs.h"

#define LABEL_WIDTH_OFFSET -0.05f
#define LABEL_HEIGHT_OFFSET -0.03f

Screen::Screen(std::shared_ptr<const Sprite> cursorSprite, Layer& layer)
	: _cursorSprite(cursorSprite)
	, _layer(layer)
	, _selectedElement(nullptr)
	, _elementLabel("")
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
	}
	
	if (_selectedElement)
	{
		_cursorElementRelativePos = _cursorPos - _selectedElement->getScreenPos();
		bool unSelectElement = false;
		if (_selectedElement->coversPoint(_cursorPos))
		{
			_selectedElement->onHover(_cursorElementRelativePos);
		}
		else
		{
			unSelectElement = true;
		}
		if (in.pollMouse(MOUSESTATE_CLICKED))
		{
			_selectedElement->onClick(_cursorElementRelativePos);
		}
		if (in.pollMouse(MOUSESTATE_CLICK_HELD))
		{
			_selectedElement->onClickHold(_cursorElementRelativePos);
			unSelectElement = false;
		}
		if (in.pollMouse(MOUSESTATE_RELEASED))
		{
			_selectedElement->onRelease(_cursorElementRelativePos);
			if (!_selectedElement->coversPoint(_cursorPos))
			{
				unSelectElement = true;
			}
		}
		if (unSelectElement)
		{
			unSelectScreenElement();
		}
	}
	Vec2 cursorVisPos(_cursorPos.x, _cursorPos.y - _cursorSprite->size.y);
	_layer.submitSprite(_cursorSprite, cursorVisPos, Vec3(0, 0, -1));
	if (_elementLabel != "")
	{
		_layer.submitText(_elementLabel, cursorVisPos + Vec2(LABEL_WIDTH_OFFSET, LABEL_HEIGHT_OFFSET), 0.2f);
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
			_elementLabel = screenElement->getLabel();
			return;
		}
	}
	_selectedElement = nullptr;
}

void Screen::unSelectScreenElement()
{
	_selectedElement->onExit(_cursorElementRelativePos);
	_selectedElement = nullptr;
	_elementLabel = "";
}