#include  "menustate.h"
#include "../../input/input.h"
#include "../../graphics/layer.h"

State_Condition MenuState::update(Game& game)
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
	layer.submitQuad(Vec2(0, 0), Vec2(0.3f, 0.3f), Vec4(1.0f, 0, 0, 1.0f));
}

Vec2 MenuState::getInContextPosition(const Vec2& screenPosition) const
{
	return screenPosition;
}