#include "easyWindow.h"
#include "easyExcept.h"

extern LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace easyXPlus
{
	/////////////////////////////////////////////////////////////////////////////////////

	bool Window::registered = false;

	/////////////////////////////////////////////////////////////////////////////////////

	Window::Window() : Window(INIT_POS_X, INIT_POS_Y, INIT_WIDTH, INIT_HEIGHT)
	{
	}

	Window::Window(unsigned posX, unsigned posY) : Window(posX, posY, INIT_WIDTH, INIT_HEIGHT)
	{
	}

	Window::Window(unsigned posX, unsigned posY, unsigned width, unsigned height)
	{
		registerWindowClass();
		createWindow(posX, posY, width, height);
		ShowWindow(windowHandle, SW_SHOW);
		UpdateWindow(windowHandle); 
	}

	///////////////////////////////////////

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
		::SetBkColor(GetDC(windowHandle), RGB(23,34,45));
	}

	////////////////////////////////////////  END  //////////////////////////////////////
}