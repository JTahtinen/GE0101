#include "editor.h"
#include "../../input/input.h"
#include "../../application/application.h"

Editor::Editor(Window& win, std::weak_ptr<Sprite> cursorSprite)
	: State(win, cursorSprite, "editor")
{
}

Editor::~Editor()
{

}

State_Condition Editor::update(Application& app)
{
	static Input& in = Input::instance();
	if (in.pollKeyboard(KEY_ESCAPE, KEYSTATE_TYPED))
	{
		app.setCurrentState("menu");
		return STATE_FINISHED;
	}
	return STATE_RUNNING;
}

void Editor::render(Layer& layer)
{
	State::render(layer);
}

Vec2 Editor::getInContextPosition(const Vec2& screenPosition) const
{
	return screenPosition;
}