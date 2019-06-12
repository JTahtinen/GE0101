#include "inputcontroller.h"
#include "../../../input/input.h"

void InputController::update(Actor* e)
{
	static float speed = 1.0f;
	static float runningSpeed = 1.8f;
	static float currentSpeed = speed;
	Input& in = Input::instance();
	if (in.poll(KEY_LSHIFT))
	{
		currentSpeed = runningSpeed;
	}
	else if (in.poll(KEY_LSHIFT, KEYSTATE_RELEASED))
	{
		currentSpeed = speed;
	}
	if (in.poll(KEY_A))
	{
		e->move(Vec2(-1.0f, 0), currentSpeed);
	}
	if (in.poll(KEY_D))
	{
		e->move(Vec2(1.0f, 0), currentSpeed);
	}
	if (in.poll(KEY_W))
	{
		e->move(Vec2(0, 1.0f), currentSpeed);
	}
	if (in.poll(KEY_S))
	{
		e->move(Vec2(0, -1.0f), currentSpeed);
	}
}