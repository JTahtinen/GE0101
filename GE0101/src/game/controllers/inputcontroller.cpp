#include "inputcontroller.h"
#include "../../input/input.h"

void InputController::update(Actor* e)
{
	static float speed = 0.01f;
	Input& in = Input::instance();
	if (in.poll(KEY_LEFT))
	{
		e->addVel(Vec2(-speed, 0));
	}
	if (in.poll(KEY_RIGHT))
	{
		e->addVel(Vec2(speed, 0));
	}
	if (in.poll(KEY_UP))
	{
		e->addVel(Vec2(0, speed));
	}
	if (in.poll(KEY_DOWN))
	{
		e->addVel(Vec2(0, -speed));
	}
}