#include "easyKeyboard.h"
#include "easyWindow.h"

#include <cassert>

namespace easyXPlus
{
	///////////////////////////////////////////////////////////////////////////
	//								Keyboard

	bool Keyboard::isPressed(Key key)
	{
		int virtualKey = convertToVirtualKey(key);
		return GetAsyncKeyState(virtualKey) != 0;
	}

	int Keyboard::convertToVirtualKey(Key key)
	{
		switch (key)
		{
		case Key::Key0:		return 0x30;
		case Key::Key1:		return 0x31;
		case Key::Key2:		return 0x32;
		case Key::Key3:		return 0x33;
		case Key::Key4:		return 0x34;
		case Key::Key5:		return 0x35;
		case Key::Key6:		return 0x36;
		case Key::Key7:		return 0x37;
		case Key::Key8:		return 0x38;
		case Key::Key9:		return 0x39;

		case Key::KeyA:		return 0x41;
		case Key::KeyB:		return 0x42;
		case Key::KeyC:		return 0x43;
		case Key::KeyD:		return 0x44;
		case Key::KeyE:		return 0x45;
		case Key::KeyF:		return 0x46;
		case Key::KeyG:		return 0x47;
		case Key::KeyH:		return 0x48;
		case Key::KeyI:		return 0x49;
		case Key::KeyJ:		return 0x4A;
		case Key::KeyK:		return 0x4B;
		case Key::KeyL:		return 0x4C;
		case Key::KeyM:		return 0x4D;
		case Key::KeyN:		return 0x4E;
		case Key::KeyO:		return 0x4F;
		case Key::KeyP:		return 0x50;
		case Key::KeyQ:		return 0x51;
		case Key::KeyR:		return 0x52;
		case Key::KeyS:		return 0x53;
		case Key::KeyT:		return 0x54;
		case Key::KeyU:		return 0x55;
		case Key::KeyV:		return 0x56;
		case Key::KeyW:		return 0x57;
		case Key::KeyX:		return 0x58;
		case Key::KeyY:		return 0x59;
		case Key::KeyZ:		return 0x5A;

		case Key::KeyLeftShift:		return VK_LSHIFT;
		case Key::KeyLeftCtrl:		return VK_LCONTROL;
		case Key::KeyLeftAlt:		return VK_LMENU;
		case Key::KeyRightShift:	return VK_RSHIFT;
		case Key::KeyRightCtrl:		return VK_RCONTROL;
		case Key::KeyRightAlt:		return VK_RMENU;

		case Key::KeyUpArrow:		return VK_UP;
		case Key::KeyDownArrow:		return VK_DOWN;
		case Key::KeyLeftArrow:		return VK_LEFT;
		case Key::KeyRightArrow:	return VK_RIGHT;

		case Key::KeyEsc:			return VK_ESCAPE;
		case Key::KeyTab:			return VK_TAB;
		case Key::KeySpace:			return VK_SPACE;
		case Key::KeyEnter:			return VK_RETURN;
		case Key::KeyBackspace:		return VK_BACK;
		default:
			assert(false && "Key not supported!");
		}
	}
}