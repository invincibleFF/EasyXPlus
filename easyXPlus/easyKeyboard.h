#ifndef EASY_KEYBOARD_H
#define EASY_KEYBOARD_H

#include <windows.h>

namespace easyXPlus
{
	enum class Key
	{
		KeyNone,

		KeyA, KeyB, KeyC, KeyD, KeyE, KeyF, KeyG, KeyH, KeyI,
		KeyJ, KeyK, KeyL, KeyM, KeyN, KeyO, KeyP, KeyQ, KeyR,
		KeyS, KeyT, KeyU, KeyV, KeyW, KeyX, KeyY, KeyZ,

		Key0, Key1, Key2, Key3, Key4, Key5, Key6, Key7, Key8,
		Key9,

		KeyLeftShift, KeyLeftCtrl, KeyLeftAlt,
		KeyRightShift, KeyRightCtrl, KeyRightAlt,
		KeyUpArrow, KeyDownArrow, KeyLeftArrow, KeyRightArrow,
		KeyEsc, KeyTab, KeySpace, KeyEnter, KeyBackspace
	};

	class Keyboard
	{
	public:
		static bool isPressed(Key key);

	private:
		static int convertToVirtualKey(Key key);
	};
}

#endif