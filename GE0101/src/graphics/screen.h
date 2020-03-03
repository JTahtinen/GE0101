#pragma once
#include "sprite.h"
#include "screenelement.h"
#include <vector>
#include "window.h"

class Screen
{
	std::shared_ptr<const Sprite>						_cursorSprite;
	Vec2												_cursorPos;
	std::vector<ScreenElement*>							_screenElements;
	ScreenElement*										_selectedElement;
public:
	Screen(std::shared_ptr<const Sprite> cursorSprite);
	void update(const Window& win);
	void addScreenElement(ScreenElement* screenElement);
private:
	void selectScreenElement(const Window& win);
};