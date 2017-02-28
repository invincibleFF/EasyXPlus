#include "easyMouse.h"
#include "easyWindow.h"
#include "easyExcept.h"
#include <algorithm>

using namespace std;

namespace easyXPlus
{
	//////////////////////////////////////////////////////////////////////////
	//								Mouse class

	Point Mouse::getCurrentPos()
	{
		POINT pos;
		if (0 == GetCursorPos(&pos))
			throw EasyExcept("System call error!");

		if (0 == ScreenToClient(Window::getDefaultWindowHandle(), &pos))
			throw EasyExcept("System call error!");

		return Point(pos.x, pos.y);
	}

	//////////////////////////////////////////////////////////////////////////

	MouseEvent Mouse::tryGetEvent()
	{
		MSG msg;
		if (0 == PeekMessageW(
					&msg,
					Window::getDefaultWindowHandle(),
					WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE))
			return MouseEvent::None;
		
		switch (msg.message)
		{
		case WM_LBUTTONDOWN:	return MouseEvent::LeftDown;
		case WM_LBUTTONUP:		return MouseEvent::LeftUp;
		case WM_RBUTTONDOWN:	return MouseEvent::RightDown;
		case WM_RBUTTONUP:		return MouseEvent::RightUp;
		case WM_MOUSEMOVE:		return MouseEvent::Move;
		default:				return MouseEvent::None;
		}
	}

}