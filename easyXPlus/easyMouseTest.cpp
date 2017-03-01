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

void HasEvent_NoEvent_ReturnFalse()
{
	Window window;
	window.setAsDefault();

	assert(Mouse::hasEvents() == false);
}

void HasEvent_SupportedEvent_AlwaysReturnTrue()
{
	Window window;
	window.setAsDefault();
	PostMessageW(Window::getDefaultWindowHandle(), WM_RBUTTONDOWN, 0, 0);

	assert(Mouse::hasEvents() == true);
	assert(Mouse::hasEvents() == true);
}

void HasEvent_NotSupportedEvent_AlwaysReturnFalse()
{
	Window window;
	window.setAsDefault();
	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONDBLCLK, 0, 0);

	assert(Mouse::hasEvents() == false);
	assert(Mouse::hasEvents() == false);
}

void HasEvent_NotSupportedEvent_RemoveIt()
{
	Window window;
	window.setAsDefault();
	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONDBLCLK, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_MOUSEMOVE, 0, 0);

	Mouse::hasEvents();

	assert(Mouse::getEvent() == MouseEvent::Move);
}

void HasEvent_AfterGetEventCall_ReturnFalse()
{
	Window window;
	window.setAsDefault();
	PostMessageW(Window::getDefaultWindowHandle(), WM_RBUTTONDOWN, 0, 0);

	Mouse::getEvent();

	assert(Mouse::hasEvents() == false);
}

//	Do not move mouse!!!
void GetEvent_NoEvent_ThrowExcept()
{
	Window window;
	window.setAsDefault();

	SU_ASSERT_THROW(Mouse::getEvent(), EasyExcept);
}

void GetEvent_ByDefault_ReturnMouseEvent()
{
	Window window;
	window.setAsDefault();

	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONDOWN, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_LBUTTONUP, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_RBUTTONDOWN, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_RBUTTONUP, 0, 0);
	PostMessageW(Window::getDefaultWindowHandle(), WM_MOUSEMOVE, 0, 0);

	assert(Mouse::getEvent() == MouseEvent::LeftDown);
	assert(Mouse::getEvent() == MouseEvent::LeftUp);
	assert(Mouse::getEvent() == MouseEvent::RightDown);
	assert(Mouse::getEvent() == MouseEvent::RightUp);
	assert(Mouse::getEvent() == MouseEvent::Move);
}