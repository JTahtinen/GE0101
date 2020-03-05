#pragma once
#include "sprite.h"
#include "screenelement.h"
#include <string>
#include "window.h"
#include "../graphics/layer.h"
#include <unordered_map>

class Screen
{
	Window&																	_targetWindow;
	std::shared_ptr<const Sprite>											_cursorSprite;
	Vec2																	_cursorPos;
	Vec2																	_cursorElementRelativePos;
	std::unordered_map<std::string, std::unique_ptr<ScreenElement>>			_screenElements;
	std::string																_selectedElement;
	std::string																_elementLabel;
	Layer																	_mainLayer;
	Layer																	_cursorLayer;
public:
	Screen(std::weak_ptr<const Sprite> cursorSprite, Window& target);
	void update();
	void addScreenElement(std::unique_ptr<ScreenElement> element, const std::string& label);
private:
	void selectScreenElement(const Window& win);
	void unSelectScreenElement();
};