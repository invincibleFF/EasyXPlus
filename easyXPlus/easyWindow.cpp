#include "easyWindow.h"
#include "easyExcept.h"

/////////////////////////////////////////////////////////////////////////////////////////
//	prototypes and variables in easyBase.h module

extern COLORREF g_bkColor;

 LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace easyXPlus
{
	/////////////////////////////////////////////////////////////////////////////////////

	bool Window::registered = false;
	HWND Window::defaultWindowHandle = NULL;

	/////////////////////////////////////////////////////////////////////////////////////

	Window::Window()
	{
		realCtor(INIT_POS_X, INIT_POS_Y, INIT_WIDTH, INIT_HEIGHT);
	}

	Window::Window(unsigned posX, unsigned posY)
	{
		realCtor(posX, posY, INIT_WIDTH, INIT_HEIGHT);
	}

	Window::Window(unsigned posX, unsigned posY, unsigned width, unsigned height)
	{
		realCtor(posX, posY, width, height);
	}

	///////////////////////////////////////

	void Window::realCtor(unsigned posX, unsigned posY, unsigned width, unsigned height)
	{
		registerWindowClass();
		createWindow(posX, posY, width, height);
		ShowWindow(windowHandle, SW_SHOW);
		UpdateWindow(windowHandle); 
	}

	void Window::registerWindowClass()
	{
		if (!registered)
		{
			WNDCLASSW wndclass = { 0 };
			wndclass.lpszClassName = L"easyXPlus::WindowClassName";
			wndclass.hInstance = GetModuleHandleW(NULL);			//	current .exe's module handle
			wndclass.lpfnWndProc = WindowProc;						//	default window procedure
			wndclass.hCursor = LoadCursorW(NULL, IDC_ARROW);		//	default arrow cursor
			wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW;//	default window style
			wndclass.hbrBackground = (HBRUSH)(1 + COLOR_BACKGROUND);

			if (RegisterClassW(&wndclass) == 0)
				throw EasyExcept("Cannot register window class!");
			registered = true;
		}
	}

	void Window::createWindow(unsigned posX, unsigned posY, unsigned width, unsigned height)
	{
		windowHandle = CreateWindowW(
			L"easyXPlus::WindowClassName",
			L"easyXPlus",
			WS_POPUP | WS_CAPTION,
			posX, posY,
			width, height,
			NULL, NULL,
			NULL, NULL);

		if (windowHandle == NULL)
			throw EasyExcept("Cannot create window!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::setBkColor(const Colorable& color)
	{
		g_bkColor = color.toColorref();
	}

	/////////////////////////////////////////////////////////////////////////////////////

	COLORREF Window::getBkColor() const
	{
		return GetBkColor(GetDC(windowHandle));
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::resize(unsigned width, unsigned height)
	{
		RECT oldWindowRect;
		if ( 0 == GetWindowRect(windowHandle, &oldWindowRect))
			goto call_error;

		if (0 == MoveWindow(
					windowHandle,
					oldWindowRect.left, oldWindowRect.top,
					width, height,
					FALSE))
			goto call_error;
		return;

	call_error:
		throw easyXPlus::EasyExcept("resize error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::reposition(unsigned posX, unsigned posY)
	{
		RECT windowRect;
		if (0 == GetWindowRect(windowHandle, &windowRect))
			goto call_error;

		if (0 == MoveWindow(
			windowHandle,
			posX, posY,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			FALSE))

			goto call_error;
		return;

	call_error:
		throw easyXPlus::EasyExcept("reposition error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::setAsDefault()
	{
		defaultWindowHandle = windowHandle;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	int Window::getPosX() const
	{
		return getWindowRect().left;
	}

	int Window::getPosY() const
	{
		return getWindowRect().top;
	}

	unsigned Window::getWidth() const
	{
		RECT rect = getWindowRect();
		return rect.right - rect.left;
	}

	unsigned Window::getHeight() const
	{
		RECT rect = getWindowRect();
		return rect.bottom - rect.top;
	}

	RECT Window::getWindowRect() const
	{
		RECT windowRect;
		if (0 == GetWindowRect(windowHandle, &windowRect))
			throw EasyExcept("Get Window Region error!");

		return windowRect;
	}

	////////////////////////////////////////  END  //////////////////////////////////////
}