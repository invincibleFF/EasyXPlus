#include "easyMouse.h"
#include "easyExcept.h"
#include "easyWindow.h"

#include "SU.h"

using namespace EasyXPlus;

///////////////////////////////////////////////////////////////////////////////
//									Tests

void flushMouseEvnets()
{
	while (Mouse::tryGetEvent() != MouseEvent::None)
		;
}

//	!!! Do not move mouse when running this test
void GetCurrentPos_ByDefault_GetWhereItIs()
{
	MultiWindow window;
	window.setAsDefault();
	Point expectedPoint(12, 32);

	SetCursorPos(expectedPoint.getX(), expectedPoint.getY());

	POINT point;
	Point returnPoint = Mouse::getCurrentPos();
	point.x = returnPoint.getX(), point.y = returnPoint.getY();
	ClientToScreen(MultiWindow::getDefaultWindowHandle(), &point);
	assert(Point(point.x, point.y) == expectedPoint);
}

//	Do not move mouse!!!
void TryGetEvent_NoEvent_ReturnNone()
{
	MultiWindow window;
	window.setAsDefault();
	flushMouseEvnets();

	MouseEvent ev = Mouse::tryGetEvent();
	assert(ev == MouseEvent::None);
}

void TryGetEvent_SupportedEvent_ReturnEvent()
{
	MultiWindow window;
	window.setAsDefault();

	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_LBUTTONDOWN, 0, 0);
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_LBUTTONUP, 0, 0);
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_RBUTTONDOWN, 0, 0);
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_RBUTTONUP, 0, 0);
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_MOUSEMOVE, 0, 0);

	assert(Mouse::tryGetEvent() == MouseEvent::LeftDown);
	assert(Mouse::tryGetEvent() == MouseEvent::LeftUp);
	assert(Mouse::tryGetEvent() == MouseEvent::RightDown);
	assert(Mouse::tryGetEvent() == MouseEvent::RightUp);
	assert(Mouse::tryGetEvent() == MouseEvent::Move);
}

void TryGetEvent_NotSupportedEvent_ReturnNone()
{
	MultiWindow window;
	window.setAsDefault();
	flushMouseEvnets();
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_LBUTTONDBLCLK, 0, 0);

	assert(Mouse::tryGetEvent() == MouseEvent::None);
}

void TryGetEvent_SupportedMixedWithUnsupported_ReturnSupported()
{
	MultiWindow window;
	window.setAsDefault();
	flushMouseEvnets();

	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_LBUTTONDOWN, 0, 0);
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_NCLBUTTONDBLCLK, 0, 0);
	PostMessageW(MultiWindow::getDefaultWindowHandle(), WM_MOUSEMOVE, 0, 0);

	assert(Mouse::tryGetEvent() == MouseEvent::LeftDown);
	assert(Mouse::tryGetEvent() == MouseEvent::Move);
	assert(Mouse::tryGetEvent() == MouseEvent::None);
}