#include "easyMouse.h"
#include "easyBaseWindow.h"
#include "easyExcept.h"
#include <algorithm>

using namespace std;

namespace EasyXPlus
{
	//////////////////////////////////////////////////////////////////////////
	//								Mouse class

	Point Mouse::getCurrentPos()
	{
		POINT pos;
		if (0 == GetCursorPos(&pos))
			throw EasyExcept("System call error!");

		if (0 == ScreenToClient(BaseWindow::getDefaultWindowHandle(), &pos))
			throw EasyExcept("System call error!");

		return Point(pos.x, pos.y);
	}

	//////////////////////////////////////////////////////////////////////////

	MouseEvent Mouse::tryGetEvent()
	{
		MSG msg;
		while (0 != PeekMessageW(
						&msg,
						BaseWindow::getDefaultWindowHandle(),
						WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:	return MouseEvent::LeftDown;
			case WM_LBUTTONUP:		return MouseEvent::LeftUp;
			case WM_RBUTTONDOWN:	return MouseEvent::RightDown;
			case WM_RBUTTONUP:		return MouseEvent::RightUp;
			case WM_MOUSEMOVE:		return MouseEvent::Move;

			default:				continue;	//	skip other mouse events
			}
		}
		return MouseEvent::None;
	}

}