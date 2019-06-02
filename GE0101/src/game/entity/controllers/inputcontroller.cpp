#include "inputcontroller.h"
#include "../../../input/input.h"

void InputController::update(Actor* e)
{
	float speed = 1.0f;
	Input& in = Input::instance();
	if (in.poll(KEY_A))
	{
		e->move(Vec2(-1.0f, 0), speed);
	}
	if (in.poll(KEY_D))
	{
		e->move(Vec2(1.0f, 0), speed);
	}
	if (in.poll(KEY_W))
	{
		e->move(Vec2(0, 1.0f), speed);
	}
	if (in.poll(KEY_S))
	{
		e->move(Vec2(0, -1.0f), speed);
	}
}