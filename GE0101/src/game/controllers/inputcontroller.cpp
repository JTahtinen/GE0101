#include "inputcontroller.h"
#include "../../input/input.h"

void InputController::update(Actor* e)
{
	static float speed = 0.01f;
	Input& in = Input::instance();
	if (in.poll(KEY_LEFT))
	{
		e->addForce(Vec2(-speed, 0));
	}
	if (in.poll(KEY_RIGHT))
	{
		e->addForce(Vec2(speed, 0));
	}
	if (in.poll(KEY_UP))
	{
		e->addForce(Vec2(0, speed));
	}
	if (in.poll(KEY_DOWN))
	{
		e->addForce(Vec2(0, -speed));
	}
}