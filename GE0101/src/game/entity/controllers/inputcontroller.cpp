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
		//currentSpeed = runningSpeed;
		e->addCommand(COMMAND_INCREASE_SPEED);
	}
	else if (in.poll(KEY_LSHIFT, KEYSTATE_RELEASED))
	{
		//currentSpeed = speed;
		e->addCommand(COMMAND_DECREASE_SPEED);
	}
	if (in.poll(KEY_A))
	{
		//e->move(Vec2(-1.0f, 0), currentSpeed);
		e->addCommand(COMMAND_MOVE_LEFT);
	}
	if (in.poll(KEY_D))
	{
		//e->move(Vec2(1.0f, 0), currentSpeed);
		e->addCommand(COMMAND_MOVE_RIGHT);
	}
	if (in.poll(KEY_W))
	{
		//e->move(Vec2(0, 1.0f), currentSpeed);
		e->addCommand(COMMAND_MOVE_UP);
	}
	if (in.poll(KEY_S))
	{
		//e->move(Vec2(0, -1.0f), currentSpeed);
		e->addCommand(COMMAND_MOVE_DOWN);
	}
}