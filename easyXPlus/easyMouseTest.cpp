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

//	Do not move mouse!!!
void TryGetEvent_NoEvent_ReturnNone()
{
	Window window;
	window.setAsDefault();

	assert(Mouse::tryGetEvent() == MouseEvent::None);
}

void TryGetEvent_SupportedEvent_ReturnEvent()
{
	Window window;
	window.setAsDefault();

	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONDOWN, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONUP, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_RBUTTONDOWN, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_RBUTTONUP, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_MOUSEMOVE, 0, 0);

	assert(Mouse::tryGetEvent() == MouseEvent::LeftDown);
	assert(Mouse::tryGetEvent() == MouseEvent::LeftUp);
	assert(Mouse::tryGetEvent() == MouseEvent::RightDown);
	assert(Mouse::tryGetEvent() == MouseEvent::RightUp);
	assert(Mouse::tryGetEvent() == MouseEvent::Move);
}

void TryGetEvent_NotSupportedEvent_ReturnNone()
{
	Window window;
	window.setAsDefault();

	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONDBLCLK, 0, 0);

	assert(Mouse::tryGetEvent() == MouseEvent::None);
}

void TryGetEvent_SupportedMixedWithUnsupported_ReturnSupported()
{
	Window window;
	window.setAsDefault();

	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONDOWN, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_NCLBUTTONDBLCLK, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_MOUSEMOVE, 0, 0);

	assert(Mouse::tryGetEvent() == MouseEvent::LeftDown);
	assert(Mouse::tryGetEvent() == MouseEvent::Move);
	assert(Mouse::tryGetEvent() == MouseEvent::None);
}