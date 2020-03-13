#include "frame.h"
#include "../defs.h"

Frame::Frame(const Vec2& pos, const Vec2& dimensions)
	: ScreenElement(pos, dimensions)
{

}

void Frame::onHover(const Vec2& relativePos)
{
	//MSG("Hovering on " << relativePos.toString());
}

void Frame::onClick(const Vec2& relativePos)
{
	MSG("Mouse clicked on frame");
}

void Frame::onClickHold(const Vec2& relativePos)
{
}

void Frame::onRelease(const Vec2& relativePos)
{
	MSG("Mouse released on frame");
}

void Frame::onReleaseHover(const Vec2& relativePos)
{
}

void Frame::onExitHoverNoRelease(const Vec2& relativePos)
{
}

void Frame::onExit(const Vec2& relativePos)
{
	MSG("Mouse exited frame");
}

void Frame::render(Layer& layer, const Vec2& pos) const
{
	//layer.submitQuad(_posStart + pos, _dimensions + pos, Vec4(1.0f, 0, 0, 1.0f));
	for (const std::shared_ptr<const ScreenElement> child : _children)
	{
		if (child)
		{
			child->render(layer, _posStart + pos);
		}
	}
}