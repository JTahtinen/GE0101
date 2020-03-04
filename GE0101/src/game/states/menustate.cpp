#include  "menustate.h"
#include "../../input/input.h"
#include "../../graphics/layer.h"

State_Condition MenuState::update(Application& app)
{
	Input& in = Input::instance();
	if (in.pollKeyboard(KEY_Q, KEYSTATE_TYPED))
	{
		return STATE_FINISHED;
	}
	return STATE_RUNNING;
}

void MenuState::render(Layer& layer)
{
}

Vec2 MenuState::getInContextPosition(const Vec2& screenPosition) const
{
	return screenPosition;
}