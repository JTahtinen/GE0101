#include "screen.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"

#define LABEL_WIDTH_OFFSET -0.05f
#define LABEL_HEIGHT_OFFSET -0.03f

Screen::Screen(std::shared_ptr<const Sprite> cursorSprite, Window& win)
	: _cursorSprite(cursorSprite)
	, _uiLayer(win, g_assetManager.get<Font>("res/fonts/liberation_serif"))
	, _cursorLayer(win, g_assetManager.get<Font>("res/fonts/liberation_serif"))
	, _selectedElement(nullptr)
	, _elementLabel("")
{
	_screenElements.reserve(500);
}

void Screen::update(const Window& win)
{
	_uiLayer.begin();
	_cursorLayer.begin();
	static Input& in = Input::instance();
	_cursorPos = win.getScreenCoordsRatioCorrected(in.getMouseX(), win.getHeight() - in.getMouseY());
	
	bool firstCycle = false;
	if (!_selectedElement)
	{
		if (!in.pollMouse(MOUSESTATE_CLICK_HELD))
		{
			selectScreenElement(win);
			if (_selectedElement)
			{
				firstCycle = true;
			}
		}
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
			if (!_selectedElement->coversPoint(_cursorPos))
			{
				_selectedElement->onExitHoverNoRelease(_cursorElementRelativePos);
			}
		}
		if (!firstCycle && in.pollMouse(MOUSESTATE_RELEASED))
		{
			_selectedElement->onRelease(_cursorElementRelativePos);
			if (_selectedElement->coversPoint(_cursorPos))
			{
				_selectedElement->onReleaseHover(_cursorElementRelativePos);
			}
			else 
			{
				unSelectElement = true;
			}
		}
		if (unSelectElement)
		{
			unSelectScreenElement();
		}
		firstCycle = false;
	}

	for (auto& element : _screenElements)
	{
		element->render(_uiLayer);
	}

	Vec2 cursorVisPos(_cursorPos.x, _cursorPos.y - _cursorSprite->size.y);
	_cursorLayer.submitSprite(_cursorSprite, cursorVisPos, Vec3(0, 0, -1));
	if (_elementLabel != "")
	{
		_cursorLayer.submitText(_elementLabel, cursorVisPos + Vec2(LABEL_WIDTH_OFFSET, LABEL_HEIGHT_OFFSET), 0.2f);
	}
	_uiLayer.end();
	_uiLayer.flush();
	
	_cursorLayer.end();
	_cursorLayer.flush();
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