#include "input.h"

Input::Input()
	: _mWheelDown(false)
	, _mWheelUp(false)
	, _mouseClicked(false)
	, _mouseReleased(false)
	, _mouseClickHeld(false)
{
	SDL_GetMouseState(&_mouseX, &_mouseY);
	int i;

	for (i = 0; i < KEY_AMOUNT; ++i)
	{
		_keysPressed[i] = false;
		_keysTyped[i] = false;
		_keysReleased[i] = false;
	}
}

void Input::update()
{
	_mWheelDown = false;
	_mWheelUp = false;
	_mouseClicked = false;
	_mouseReleased = false;

	static bool keyEventHappened = false;

	if (keyEventHappened)
	{
		for (int i = 0; i < KEY_AMOUNT; ++i)
		{
			_keysReleased[i] = false;
			_keysTyped[i] = false;
		}
		keyEventHappened = false;
	}
	_deltaX = 0;
	_deltaY = 0;
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		bool keydown = (ev.type == SDL_KEYDOWN);
		bool keyup = (ev.type == SDL_KEYUP);
		if (keydown || keyup)
		{
			Key key = translateSDLKey(ev.key.keysym.sym);

			if (key == KEY_NULL) continue;

			keyEventHappened = true;

			if (keydown)
			{
				_keysPressed[key] = true;
				_keysTyped[key] = true;
			}
			else if (keyup)
			{
				_keysReleased[key] = true;
				_keysPressed[key] = false;

			}
		} else
		if (ev.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&_mouseX, &_mouseY);
			_deltaX = ev.motion.xrel; 
			_deltaY = ev.motion.yrel;
		}
		else
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)
				{
					_mouseClicked = true;
					_mouseClickHeld = true;
				}
			} else
				if (ev.type == SDL_MOUSEBUTTONUP)
				{
					if (ev.button.button == SDL_BUTTON_LEFT)
					{
						_mouseReleased = true;
						_mouseClickHeld = false;
					}
				}
			if (ev.type == SDL_MOUSEWHEEL)
		{
				if (ev.wheel.y < 0)
				{
					_mWheelDown = true;
				}
				else
				{
					_mWheelUp = true;
				}
		}
	}
	
}

bool Input::pollKeyboard(Key key, KeyState state) const
{
	if (state >= KEY_AMOUNT)
		return false;

	switch (state)
	{
	case KEYSTATE_PRESSED:
		return _keysPressed[key];
	case KEYSTATE_TYPED:
		return _keysTyped[key];
	case KEYSTATE_RELEASED:
		return _keysReleased[key];
	default:
		return false;
	}
}

bool Input::pollKeyboard(Key key) const
{
	return pollKeyboard(key, KEYSTATE_PRESSED);
}

bool Input::pollKeyboard(unsigned int key, KeyState state) const
{
	return pollKeyboard((Key)key, state);
}

bool Input::pollKeyboard(unsigned int key) const
{
	return pollKeyboard((Key)key);
}

bool Input::pollMouse(MouseState state) const
{
	switch (state)
	{
	case MOUSESTATE_CLICKED:
		return _mouseClicked;
	case MOUSESTATE_CLICK_HELD:
		return _mouseClickHeld;
	case MOUSESTATE_RELEASED:
		return _mouseReleased;
	}
	return false;
}

Key Input::translateSDLKey(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_a:
		return KEY_A;
	case SDLK_b:
		return KEY_B;
	case SDLK_c:
		return KEY_C;
	case SDLK_d:
		return KEY_D;
	case SDLK_e:
		return KEY_E;
	case SDLK_f:
		return KEY_F;
	case SDLK_g:
		return KEY_G;
	case SDLK_h:
		return KEY_H;
	case SDLK_i:
		return KEY_I;
	case SDLK_j:
		return KEY_J;
	case SDLK_k:
		return KEY_K;
	case SDLK_l:
		return KEY_L;
	case SDLK_m:
		return KEY_M;
	case SDLK_n:
		return KEY_N;
	case SDLK_o:
		return KEY_O;
	case SDLK_p:
		return KEY_P;
	case SDLK_q:
		return KEY_Q;
	case SDLK_r:
		return KEY_R;
	case SDLK_s:
		return KEY_S;
	case SDLK_t:
		return KEY_T;
	case SDLK_u:
		return KEY_U;
	case SDLK_v:
		return KEY_V;
	case SDLK_w:
		return KEY_W;
	case SDLK_x:
		return KEY_X;
	case SDLK_y:
		return KEY_Y;
	case SDLK_z:
		return KEY_Z;
	case SDLK_UP:
		return KEY_UP;
	case SDLK_DOWN:
		return KEY_DOWN;
	case SDLK_LEFT:
		return KEY_LEFT;
	case SDLK_RIGHT:
		return KEY_RIGHT;
	case SDLK_SPACE:
		return KEY_SPACE;
	case SDLK_RETURN:
		return KEY_ENTER;
	case SDLK_ESCAPE:
		return KEY_ESCAPE;
	case SDLK_LCTRL:
		return KEY_LCTRL;
	case SDLK_RCTRL:
		return KEY_RCTRL;
	case SDLK_LALT:
		return KEY_LALT;
	case SDLK_RALT:
		return KEY_RALT;
	case SDLK_0:
		return KEY_0;
	case SDLK_1:
		return KEY_1;
	case SDLK_2:
		return KEY_2;
	case SDLK_3:
		return KEY_3;
	case SDLK_4:
		return KEY_4;
	case SDLK_5:
		return KEY_5;
	case SDLK_6:
		return KEY_6;
	case SDLK_7:
		return KEY_7;
	case SDLK_8:
		return KEY_8;
	case SDLK_9:
		return KEY_9;
	default:
	case SDLK_LSHIFT:
		return KEY_LSHIFT;
	case SDLK_RSHIFT:
		return KEY_RSHIFT;
		return KEY_NULL;
	}
}
