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
}