#include "easyMouse.h"
#include "easyExcept.h"
#include "easyWindow.h"

#include "SU.h"

using namespace easyXPlus;

//	!!! Do not move mouse when running this test
void GetCurrentPos_ByDefault_GetWhereItIs()
{
	Window window;
	window.setAsDefault();
	Point expectedPoint(12, 32);

	SetCursorPos(expectedPoint.getX(), expectedPoint.getY());

	POINT point;
	Point returnPoint = Mouse::getCurrentPos();
	point.x = returnPoint.getX(), point.y = returnPoint.getY();
	ClientToScreen(Window::getDefaultWindowHandle(), &point);
	assert(Point(point.x, point.y) == expectedPoint);
}