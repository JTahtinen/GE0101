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
	, _selectedFrame(NULL_ELEMENT)
	, _elementLabel("")
{
	_frames.reserve(8);
}

void Screen::update()
{
	_mainLayer.begin();
	_cursorLayer.begin();
	static Input& in = Input::instance();
	_cursorPos = _targetWindow.getScreenCoordsRatioCorrected(in.getMouseX(), _targetWindow.getHeight() - in.getMouseY());
	
	//bool firstCycle = false;
	//if (_selectedFrame == NULL_ELEMENT)
	//{
	//	if (!in.pollMouse(MOUSESTATE_CLICK_HELD))
	//	{
	//		selectFrame(_targetWindow);
	//		if (_selectedFrame != NULL_ELEMENT)
	//		{
	//			firstCycle = true;
	//		}
	//	}
	//}
	//
	//if (_selectedFrame != NULL_ELEMENT)
	//{
	//	auto& frame = _frames[_selectedFrame];
	//	_cursorElementRelativePos = _cursorPos - frame->getPos();
	//	bool unSelectElement = false;
	//	if (frame->coversPoint(_cursorPos))
	//	{
	//
	//		frame->onHover(_cursorElementRelativePos);
	//		
	//	}
	//	else
	//	{
	//		unSelectElement = true;
	//	}
	//	if (in.pollMouse(MOUSESTATE_CLICKED))
	//	{
	//		frame->onClick(_cursorElementRelativePos);
	//	}
	//	if (in.pollMouse(MOUSESTATE_CLICK_HELD))
	//	{
	//		frame->onClickHold(_cursorElementRelativePos);
	//		unSelectElement = false;
	//		if (!frame->coversPoint(_cursorPos))
	//		{
	//			frame->onExitHoverNoRelease(_cursorElementRelativePos);
	//		}
	//	}
	//	if (!firstCycle && in.pollMouse(MOUSESTATE_RELEASED))
	//	{
	//		frame->onRelease(_cursorElementRelativePos);
	//		if (frame->coversPoint(_cursorPos))
	//		{
	//			frame->onReleaseHover(_cursorElementRelativePos);
	//		}
	//		else 
	//		{
	//			unSelectElement = true;
	//		}
	//	}
	//	if (unSelectElement)
	//	{
	//		unSelectFrame();
	//	}
	//	firstCycle = false;
	//}


	for (auto& frame : _frames)
	{
		frame.second->update(_cursorPos);
		frame.second->render(_mainLayer, Vec2(0, 0));
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

void Screen::addFrame(FrameType type, const char* label)
{
	if (frameExists(label))
	{
		ERR("[SCREEN] Could not create frame: " << label << ". Label collision!");
		return;
	}
	
	float screenRatio = _targetWindow.getRatio();
	Vec2 screenStart(-1.0f, -1.0f / screenRatio);
	Vec2 dimensions(2.0f, 2.0f / screenRatio);
	switch (type)
	{
	case FRAMETYPE_FULL:
		_frames[label] = std::make_unique<Frame>(screenStart, dimensions);
		break;
	default:
		break;
	}
}

void Screen::addScreenElement(std::weak_ptr<ScreenElement> screenElement, const char* frame)
{
	if (frameExists(frame))
	{
		_frames[frame]->addChild(screenElement);
	}
}

void Screen::removeScreenElement(std::weak_ptr<const ScreenElement> element)
{
	for (auto& frame : _frames)
	{
		frame.second->removeChild(element);
	}
}

void Screen::selectFrame(const Window& win)
{
	for (auto& frame : _frames)
	{
		auto& potentialFrame = frame.second;	
		if (potentialFrame->coversPoint(_cursorPos))
		{
			_selectedFrame = frame.first;
			_elementLabel = potentialFrame->getLabel();
			return;
		}
	}
	_selectedFrame = NULL_ELEMENT;
}

void Screen::unSelectFrame()
{
	if (_selectedFrame != NULL_ELEMENT)
	{
		_frames[_selectedFrame]->onExit(_cursorElementRelativePos);
		_selectedFrame = NULL_ELEMENT;
	}
	_elementLabel = "";
}

bool Screen::frameExists(const char* label) const
{
	for (const auto& frame : _frames)
	{
		if (frame.first == label)
		{
			return true;
		}
	}
	return false;
}