#include "inputcontroller.h"
#include "../../input/input.h"

void InputController::update(Actor* e)
{
	float speed = 1.0f;
	Input& in = Input::instance();
	if (in.poll(KEY_A))
	{
		e->addForce(Vec2(-speed, 0));
	}
	if (in.poll(KEY_D))
	{
		e->addForce(Vec2(speed, 0));
	}
	if (in.poll(KEY_W))
	{
		e->addForce(Vec2(0, speed));
	}
	if (in.poll(KEY_S))
	{
		e->addForce(Vec2(0, -speed));
	}
}