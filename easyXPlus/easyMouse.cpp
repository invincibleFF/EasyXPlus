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

	bool Mouse::hasEvents()
	{
		MSG msg;
		if (0 == PeekMessageW(
						&msg,
						Window::getDefaultWindowHandle(),
						WM_MOUSEFIRST, WM_MOUSELAST, PM_NOREMOVE))
			return false;

		switch (msg.message)
		{
		case WM_LBUTTONDOWN:		//	fall through
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MOUSEMOVE:			return true;
		default:					return false;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	MouseEvent Mouse::getEvent()
	{
		MSG msg;
		if (0 == PeekMessageW(
					&msg,
					Window::getDefaultWindowHandle(),
					WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE))
					throw EasyExcept("Has no events!");
		
		switch (msg.message)
		{
		case WM_LBUTTONDOWN:	return MouseEvent::LeftDown;
		case WM_LBUTTONUP:		return MouseEvent::LeftUp;
		case WM_RBUTTONDOWN:	return MouseEvent::RightDown;
		case WM_RBUTTONUP:		return MouseEvent::RightUp;
		case WM_MOUSEMOVE:		return MouseEvent::Move;
		default:				throw EasyExcept("Has no supported events!");
		}
	}

}