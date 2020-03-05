#include "screen.h"
#include "../input/input.h"
#include "../defs.h"
#include "../globals.h"
#include "label.h"

#define LABEL_WIDTH_OFFSET -0.05f
#define LABEL_HEIGHT_OFFSET -0.03f

#define NULL_ELEMENT "NULL_ELEMENT"

Screen::Screen(std::weak_ptr<const Sprite> cursorSprite, Window& target)
	: _cursorSprite(cursorSprite)
	, _targetWindow(target)
	, _mainLayer(target, g_assetManager.get<Font>("res/fonts/liberation_serif"))
	, _cursorLayer(target, g_assetManager.get<Font>("res/fonts/liberation_serif"))
	, _selectedElement(NULL_ELEMENT)
	, _elementLabel("")
{
	_screenElements.reserve(500);
}

void Screen::update()
{
	_mainLayer.begin();
	_cursorLayer.begin();
	static Input& in = Input::instance();
	_cursorPos = _targetWindow.getScreenCoordsRatioCorrected(in.getMouseX(), _targetWindow.getHeight() - in.getMouseY());
	
	bool firstCycle = false;
	if (_selectedElement == NULL_ELEMENT)
	{
		if (!in.pollMouse(MOUSESTATE_CLICK_HELD))
		{
			selectScreenElement(_targetWindow);
			if (_selectedElement != NULL_ELEMENT)
			{
				firstCycle = true;
			}
		}
	}
	
	if (_selectedElement != NULL_ELEMENT)
	{
		auto& elem = _screenElements[_selectedElement];
		_cursorElementRelativePos = _cursorPos - elem->getScreenPos();
		bool unSelectElement = false;
		if (elem->coversPoint(_cursorPos))
		{
	
			elem->onHover(_cursorElementRelativePos);
			
		}
		else
		{
			unSelectElement = true;
		}
		if (in.pollMouse(MOUSESTATE_CLICKED))
		{
			elem->onClick(_cursorElementRelativePos);
		}
		if (in.pollMouse(MOUSESTATE_CLICK_HELD))
		{
			elem->onClickHold(_cursorElementRelativePos);
			unSelectElement = false;
			if (!elem->coversPoint(_cursorPos))
			{
				elem->onExitHoverNoRelease(_cursorElementRelativePos);
			}
		}
		if (!firstCycle && in.pollMouse(MOUSESTATE_RELEASED))
		{
			elem->onRelease(_cursorElementRelativePos);
			if (elem->coversPoint(_cursorPos))
			{
				elem->onReleaseHover(_cursorElementRelativePos);
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
		element.second->render(_mainLayer);
	}

	Vec2 cursorVisPos(_cursorPos.x, _cursorPos.y - _cursorSprite->size.y);
	_cursorLayer.submitSprite(_cursorSprite, cursorVisPos, Vec3(0, 0, -1));
	if (_elementLabel != "")
	{
		Label cursorLabel(_elementLabel, 0.2f);
		const Vec2& labelDim = cursorLabel.getScreenDimensions();
		cursorLabel.render(cursorVisPos - labelDim, _cursorLayer);
		//_cursorLayer.submitText(_elementLabel, cursorVisPos + Vec2(LABEL_WIDTH_OFFSET, LABEL_HEIGHT_OFFSET), 0.2f);
	}
	_mainLayer.end();
	_mainLayer.flush();
	
	_cursorLayer.end();
	_cursorLayer.flush();
}

void Screen::addScreenElement(std::unique_ptr<ScreenElement> screenElement, const std::string& label)
{
	if (screenElement)
	{
		_screenElements[label] = std::move(screenElement);
	}
}

void Screen::selectScreenElement(const Window& win)
{
	for (auto& screenElement : _screenElements)
	{
		auto& elem = screenElement.second;
		if (elem->coversPoint(_cursorPos))
		{
			_selectedElement = screenElement.first;
			_elementLabel = elem->getLabel();
			return;
		}
	}
	_selectedElement = NULL_ELEMENT;
}

void Screen::unSelectScreenElement()
{
	if (_selectedElement != NULL_ELEMENT)
	{
		_screenElements[_selectedElement]->onExit(_cursorElementRelativePos);
		_selectedElement = NULL_ELEMENT;
	}
	_elementLabel = "";
}