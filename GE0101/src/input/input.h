#pragma once

#include <SDL2/SDL.h>

enum Key
{
	KEY_A = 0,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_ENTER,
	KEY_ESCAPE,
	KEY_LCTRL,
	KEY_RCTRL,
	KEY_LALT,
	KEY_RALT,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_AMOUNT,
	KEY_NULL
};

enum KeyState
{
	KEYSTATE_PRESSED,
	KEYSTATE_TYPED,
	KEYSTATE_RELEASED
};

enum MouseState
{
	MOUSESTATE_CLICKED,
	MOUSESTATE_CLICK_HELD,
	MOUSESTATE_RELEASED
};

class Input
{
	bool		_keysPressed[KEY_AMOUNT];
	bool		_keysTyped[KEY_AMOUNT];
	bool		_keysReleased[KEY_AMOUNT];

	int			_mouseX;
	int			_mouseY;
	int			_deltaX;
	int			_deltaY;
	bool		_mWheelUp;
	bool		_mWheelDown;
	bool		_mouseClicked;
	bool		_mouseReleased;
	bool		_mouseClickHeld;

public:
	static inline Input& instance()
	{
		static Input input;
		return input;
	}
	void update();
	bool pollKeyboard(Key key, KeyState state) const;
	bool pollKeyboard(Key key) const;
	bool pollKeyboard(unsigned int key, KeyState state) const;
	bool pollKeyboard(unsigned int key) const;
	bool pollMouse(MouseState state) const;
	inline int getMouseX() const { return _mouseX; }
	inline int getMouseY() const { return _mouseY; }
	inline int getMouseDeltaX() const { return _deltaX; }
	inline int getMouseDeltaY() const { return _deltaY; }
	inline bool getMouseWheelUp() const { return _mWheelUp; }
	inline bool getMouseWheelDown() const { return _mWheelDown; }
private:
	Input();
	static Key translateSDLKey(SDL_Keycode key);
};

