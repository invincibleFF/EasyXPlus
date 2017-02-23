#ifndef EASY_KEYBOARD_H
#define EASY_KEYBOARD_H

#include <windows.h>
#include <queue>

LRESULT CALLBACK CustomeWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	private:
		friend LRESULT CALLBACK ::CustomeWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		static bool isPressing(Key key);
		static Key getPressed();

	private:
		static int convertToVirtualKey(Key key);
		static Key convertToKeyEnum(int virtualKey);

		static std::queue<Key>	keysPressed;
	};
}

#endif