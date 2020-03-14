#pragma once
#include "../math/math.h"
#include <string>
#include "layer.h"
#include "../input/input.h"

class ScreenElement
{
protected:
	std::vector<std::shared_ptr<ScreenElement>>				_children;
	Vec2													_posStart;
	Vec2													_posEnd;
	Vec2													_dimensions;
	bool													_elementSelected{ false };
public:
	ScreenElement(const Vec2& pos, const Vec2& dimensions) : _posStart(pos), _posEnd(pos + dimensions), _dimensions(dimensions)
	{
		_children.reserve(20);

	}

	void update(const Vec2& cursorPos)
	{
		static Input& in = Input::instance();

		Vec2 cursorRelativePos = cursorPos - _posStart;

		bool coversCursorPos = coversPoint(cursorPos);
		//_cursorElementRelativePos = _cursorPos - frame->getPos();
		if (coversCursorPos)
		{
			onHover(cursorRelativePos);
			_elementSelected = true;
		}
	
		if (_elementSelected)
		{
			if (in.pollMouse(MOUSESTATE_CLICKED))
			{
				onClick(cursorRelativePos);
			}
			if (in.pollMouse(MOUSESTATE_CLICK_HELD))
			{
				onClickHold(cursorRelativePos);
				//_elementSelected = false;
				if (!coversCursorPos)
				{
					onExitHoverNoRelease(cursorRelativePos);
				}
			}
			else if (!coversCursorPos)
			{
				_elementSelected = false;
			}
			if (in.pollMouse(MOUSESTATE_RELEASED))
			{
				onRelease(cursorRelativePos);
				if (coversPoint(cursorPos))
				{
					onReleaseHover(cursorRelativePos);
				}
				else
				{
					_elementSelected = false;
				}
			}

			if (!_elementSelected)
			{
				onExit(cursorRelativePos);
				return;
			}
		}


		for (std::shared_ptr<ScreenElement> child : _children)
		{
			child->update(cursorRelativePos);
		}

	}

	virtual void onHover(const Vec2& relativePos) {}
	virtual void onClick(const Vec2& relativePos) {}
	virtual void onClickHold(const Vec2& relativePos) {}
	virtual void onRelease(const Vec2& relativePos) {}
	virtual void onReleaseHover(const Vec2& relativePos) {}
	virtual void onExitHoverNoRelease(const Vec2& relativePos) {}
	virtual void onExit(const Vec2& relativePos) {}
	virtual void render(Layer& layer, const Vec2& pos) const
	{
		for (std::shared_ptr<ScreenElement> child : _children)
		{
			if (child)
			{
				child->render(layer,  _posStart + pos);
			}
		}
	}
	virtual const std::string getLabel() const { return ""; };
	inline void addChild(std::weak_ptr<ScreenElement> element)
	{
		_children.emplace_back(element);
	}
	inline void removeChild(std::weak_ptr<const ScreenElement> element)
	{
		// HACK:
		for (unsigned int i = 0; i < _children.size(); ++i)
		{
			if (_children[i] == element.lock())
			{
				_children[i] = nullptr;
			}
		}
	}
	inline void setPos(const Vec2& pos) 
	{ 
		_posStart = pos; 
		_posEnd = pos + _dimensions;
	}
	inline void setScreenDimensions(const Vec2& dimensions)
	{
		_dimensions = dimensions;
		_posEnd = _posStart + dimensions;
	}
	inline const Vec2& getPos() const { return _posStart; }
	inline bool coversPoint(const Vec2& pos) const
	{
		return math::inBounds(pos.x, _posStart.x, _posEnd.x) && math::inBounds(pos.y, _posStart.y, _posEnd.y);
	}
};