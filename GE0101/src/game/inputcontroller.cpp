#include "inputcontroller.h"
#include "../input/input.h"

void InputController::update(Entity* e) const
{
	Input& in = Input::instance();
	if (in.poll(KEY_LEFT))
	{
		e->addVel(Vec2(-1.0f, 0));
	}
	if (in.poll(KEY_RIGHT))
	{
		e->addVel(Vec2(1.0f, 0));
	}
	if (in.poll(KEY_UP))
	{
		e->addVel(Vec2(0, -1.0f));
	}
	if (in.poll(KEY_DOWN))
	{
		e->addVel(Vec2(0, 1.0f));
	}
}