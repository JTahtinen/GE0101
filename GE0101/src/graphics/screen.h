#pragma once
#include "sprite.h"
#include "screenelement.h"
#include <vector>
#include <string>
#include "window.h"
#include "../graphics/layer.h"

class Screen
{
	std::shared_ptr<const Sprite>						_cursorSprite;
	Vec2												_cursorPos;
	Vec2												_cursorElementRelativePos;
	std::vector<ScreenElement*>							_screenElements;
	ScreenElement*										_selectedElement;
	std::string											_elementLabel;
	Layer												_uiLayer;
	Layer												_cursorLayer;
public:
	Screen(std::shared_ptr<const Sprite> cursorSprite, Window& win);
	void update(const Window& win);
	void addScreenElement(ScreenElement* screenElement);
private:
	void selectScreenElement(const Window& win);
	void unSelectScreenElement();
};