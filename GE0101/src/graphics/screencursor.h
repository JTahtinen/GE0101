#pragma once
#include "sprite.h"
#include "../math/vec2.h"
#include "../input/input.h"
#include "../graphics/window.h"

class ScreenCursor
{
	std::shared_ptr<const Sprite>					_sprite;
public:
	ScreenCursor(std::shared_ptr<const Sprite> sprite);
	inline Vec2 getScreenPos(const Window& win) const
	{
		static Input& in = Input::instance();
		return win.getScreenCoordsRatioCorrected(in.getMouseX(), win.getHeight() - in.getMouseY());
	}
};