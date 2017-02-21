#include "easyMouse.h"
#include "easyExcept.h"
#include "easyWindow.h"

#include "SU.h"

using namespace easyXPlus;

//		Test Resources

unsigned g_handlerCalledTime = 0;

void* g_handlerParam = &g_handlerCalledTime;

void TestHandler(Mouse::EventParam param)
{ 
	++g_handlerCalledTime;
	g_handlerParam = param;
}


class MockWindow : public Window
{
public:
	MockWindow(Window& window) : Window(window)	{}
	~MockWindow()		{ hdc = NULL; geometryAttribute.brush = NULL; geometryAttribute.pen = NULL; textAttribute.font = NULL; }
	HWND getHandle()	{ return windowHandle; }
};

//		Test Functions

void SetEventHandler_DefaultWindowNotSet_ThrowExcept()
{
	SU_ASSERT_THROW(
		Mouse::setEventHandler(
		Mouse::EventType::LeftButtonDown, TestHandler, nullptr),
		EasyExcept);
}

void SetEventHandler_ByDefault_CalledAndParamPassedWhenEventHappens()
{
	MockWindow mockWindow(Window{});
	mockWindow.setAsDefault();
	g_handlerCalledTime = 0;
	void* paramExpected = &paramExpected;
	unsigned expectedCalledTime = 5;

	Mouse::setEventHandler(
		Mouse::EventType::LeftButtonUp, TestHandler, nullptr);
	Mouse::setEventHandler(
		Mouse::EventType::LeftButtonDown, TestHandler, nullptr);
	Mouse::setEventHandler(
		Mouse::EventType::RightButtonDown, TestHandler, nullptr);
	Mouse::setEventHandler(
		Mouse::EventType::RightButtonUp, TestHandler, nullptr);
	Mouse::setEventHandler(
		Mouse::EventType::MouseMove, TestHandler, paramExpected);
	SendMessageW(mockWindow.getHandle(), WM_LBUTTONDOWN, 0, 0);
	SendMessageW(mockWindow.getHandle(), WM_LBUTTONUP, 0, 0);
	SendMessageW(mockWindow.getHandle(), WM_RBUTTONDOWN, 0, 0);
	SendMessageW(mockWindow.getHandle(), WM_RBUTTONUP, 0, 0);
	SendMessageW(mockWindow.getHandle(), WM_MOUSEMOVE, 0, 0);

	assert(g_handlerCalledTime == expectedCalledTime);
	assert(g_handlerParam == paramExpected);
}

void NotSetHandler(Mouse::EventParam param)		{}
void CancelEventHandler_HandlerNotSet_ThrowExcept()
{
	MockWindow mockWindow(Window{});
	mockWindow.setAsDefault();

	SU_ASSERT_THROW(
		Mouse::cancelEventHandler(Mouse::EventType::LeftButtonDown, TestHandler),
		EasyExcept);
}

void CancelEventHandler_ByDefault_CancelFormerRegisteredHandler()
{
	MockWindow mockWindow(Window{});
	mockWindow.setAsDefault();
	g_handlerCalledTime = 0;

	Mouse::setEventHandler(Mouse::EventType::RightButtonDown, TestHandler, nullptr);
	Mouse::cancelEventHandler(Mouse::EventType::RightButtonDown, TestHandler);
	SendMessageW(mockWindow.getHandle(), WM_LBUTTONDOWN, 0, 0);

	assert(g_handlerCalledTime == 0);
}

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