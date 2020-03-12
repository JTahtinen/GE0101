#pragma once
#include "sprite.h"
#include "../ui/frame.h"
#include <string>
#include "window.h"
#include "../graphics/layer.h"
#include <unordered_map>

enum FrameType
{
	FRAMETYPE_FULL
};

class Screen
{
	Window&																	_targetWindow;
	std::shared_ptr<const Sprite>											_cursorSprite;
	Vec2																	_cursorPos;
	Vec2																	_cursorElementRelativePos;
	std::unordered_map<std::string, std::unique_ptr<Frame>>					_frames;
	std::string																_selectedFrame;
	std::string																_elementLabel;
	Layer																	_mainLayer;
	Layer																	_cursorLayer;
public:
	Screen(std::weak_ptr<const Sprite> cursorSprite, Window& target);
	void update();
	void addFrame(FrameType type, const char* label);
	void addScreenElement(std::weak_ptr<ScreenElement>, const char* frame);
	void removeScreenElement(std::weak_ptr<const ScreenElement> element);
private:
	void selectFrame(const Window& win);
	void unSelectFrame();
	bool frameExists(const char* label) const;
};