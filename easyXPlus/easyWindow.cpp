#include "easyWindow.h"
#include "easyExcept.h"

/////////////////////////////////////////////////////////////////////////////////////////
//	prototypes and variables in easyBase.h module

using namespace std;

namespace easyXPlus
{
	/////////////////////////////////////////////////////////////////////////////////////

	Window::Attribute* Window::getDefaultAttribute()
	{
		if (defaultAttributePtr == nullptr)
			throw EasyExcept("No default window set!");

		return defaultAttributePtr;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	bool Window::registered = false;
	Window::Attribute* Window::defaultAttributePtr = nullptr;

	/////////////////////////////////////////////////////////////////////////////////////

	Window::Window(const wstring title)
	{
		realCtor(title, INIT_POS_X, INIT_POS_Y, INIT_WIDTH, INIT_HEIGHT);
	}

	Window::Window(const wstring title, int posX, int posY)
	{
		realCtor(title, posX, posY, INIT_WIDTH, INIT_HEIGHT);
	}

	Window::Window(const wstring title, int posX, int posY, unsigned width, unsigned height)
	{
		realCtor(title, posX, posY, width, height);
	}

	Window::~Window()
	{
		//	release dc if setAsDefault() called
		if (attribute.hdc != NULL)
			if (0 == ReleaseDC(attribute.windowHandle, attribute.hdc))
				throw EasyExcept("System call error!");

		//	reset default pair if current dc equals this->hdc
		if (defaultAttributePtr ==  &attribute)
			defaultAttributePtr = nullptr;
	}

	///////////////////////////////////////

	void Window::realCtor(const wstring title, int posX, int posY, unsigned width, unsigned height)
	{
		registerWindowClass();
		createWindow(title.c_str(), posX, posY, width, height);
		ShowWindow(attribute.windowHandle, SW_SHOW);
		UpdateWindow(attribute.windowHandle); 
	}

	void Window::registerWindowClass()
	{
		if (!registered)
		{
			WNDCLASSW wndclass = { 0 };
			wndclass.lpszClassName = L"easyXPlus::WindowClassName";
			wndclass.hInstance = GetModuleHandleW(NULL);			//	current .exe's module handle
			wndclass.lpfnWndProc = DefWindowProc;					//	default window procedure
			wndclass.hCursor = LoadCursorW(NULL, IDC_ARROW);		//	default arrow cursor
			wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW;//	default window style
			wndclass.hbrBackground = (HBRUSH)(1 + COLOR_BACKGROUND);

			if (RegisterClassW(&wndclass) == 0)
				throw EasyExcept("Cannot register window class!");
			registered = true;
		}
	}

	void Window::createWindow(const wstring title, unsigned posX, unsigned posY, unsigned width, unsigned height)
	{
		attribute.windowHandle = CreateWindowW(
			L"easyXPlus::WindowClassName",
			title.c_str(),
			WS_POPUP | WS_CAPTION,
			posX, posY,
			width, height,
			NULL, NULL,
			NULL, NULL);

		if (attribute.windowHandle == NULL)
			throw EasyExcept("Cannot create window!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::clear(const Colorable& color)
	{
		HBRUSH brushHandle = CreateSolidBrush(color.toColorref());
		if (brushHandle == NULL)
			goto error;

		RECT clientRect;
		if (0 == GetClientRect(attribute.windowHandle, &clientRect))
			goto error;
		
		if (!FillRect(GetDC(attribute.windowHandle), &clientRect, brushHandle))
			goto error;

		DeleteObject((HGDIOBJ)brushHandle);
		return;

	error:
		throw EasyExcept("Window clear error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::resize(unsigned width, unsigned height)
	{
		RECT oldWindowRect;
		if ( 0 == GetWindowRect(attribute.windowHandle, &oldWindowRect))
			goto call_error;

		if (0 == MoveWindow(
					attribute.windowHandle,
					oldWindowRect.left, oldWindowRect.top,
					width, height,
					FALSE))
			goto call_error;
		return;

	call_error:
		throw easyXPlus::EasyExcept("resize error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::reposition(int posX, int posY)
	{
		RECT windowRect;
		if (0 == GetWindowRect(attribute.windowHandle, &windowRect))
			goto call_error;

		if (0 == MoveWindow(
			attribute.windowHandle,
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
		//	if first call, store HDC
		if (attribute.hdc == NULL)
		{
			attribute.hdc = GetDC(attribute.windowHandle);
			if (attribute.hdc == NULL)
				throw EasyExcept("System call error!");

			if (0 == SetArcDirection(attribute.hdc, AD_CLOCKWISE))
				throw EasyExcept("System call error!");
		}

		defaultAttributePtr = &attribute;
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
		if (0 == GetWindowRect(attribute.windowHandle, &windowRect))
			throw EasyExcept("Get Window Region error!");

		return windowRect;
	}

	////////////////////////////////////////  END  //////////////////////////////////////
}