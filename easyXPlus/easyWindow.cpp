#include "easyWindow.h"
#include "easyExcept.h"

/////////////////////////////////////////////////////////////////////////////////////////
//	prototypes and variables in easyBase.h module

using namespace std;

namespace easyXPlus
{
	/////////////////////////////////////////////////////////////////////////////////////

	Window::GeometryAttribute* Window::getDefaultGeometryAttribute()
	{
		if (defaultGeometryAttribute == nullptr)
			throw EasyExcept("No default window set!");

		return defaultGeometryAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	bool Window::registered = false;
	Window::GeometryAttribute* Window::defaultGeometryAttribute = nullptr;

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
		releaseGeometryResources();

		//	reset default pair if current dc equals this->hdc
		if (defaultGeometryAttribute ==  &geometryAttribute)
			defaultGeometryAttribute = nullptr;
	}

	void Window::releaseGeometryResources()
	{
		//	release dc if setAsDefault() called
		if (geometryAttribute.hdc != NULL)
			if (0 == ReleaseDC(geometryAttribute.windowHandle, geometryAttribute.hdc))
				throw EasyExcept("System call error!");
		if (geometryAttribute.pen != NULL)
			if (0 == DeleteObject((HGDIOBJ)geometryAttribute.pen))
				throw EasyExcept("System call error!");
		if (geometryAttribute.brush != NULL)
			if (0 == DeleteObject((HGDIOBJ)geometryAttribute.brush))
				throw EasyExcept("System call error!");
	}

	///////////////////////////////////////

	void Window::realCtor(const wstring title, int posX, int posY, unsigned width, unsigned height)
	{
		registerWindowClass();
		createWindow(title.c_str(), posX, posY, width, height);
		ShowWindow(geometryAttribute.windowHandle, SW_SHOW);
		UpdateWindow(geometryAttribute.windowHandle); 
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
		geometryAttribute.windowHandle = CreateWindowW(
			L"easyXPlus::WindowClassName",
			title.c_str(),
			WS_POPUP | WS_CAPTION,
			posX, posY,
			width, height,
			NULL, NULL,
			NULL, NULL);

		if (geometryAttribute.windowHandle == NULL)
			throw EasyExcept("Cannot create window!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::clear(const Colorable& color)
	{
		HBRUSH brush = CreateSolidBrush(color.toColorref());
		if (brush == NULL)
			goto error;

		RECT clientRect;
		if (0 == GetClientRect(geometryAttribute.windowHandle, &clientRect))
			goto error;
		
		if (!FillRect(GetDC(geometryAttribute.windowHandle), &clientRect, brush))
			goto error;

		DeleteObject((HGDIOBJ)brush);
		return;

	error:
		throw EasyExcept("Window clear error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::resize(unsigned width, unsigned height)
	{
		RECT oldWindowRect;
		if ( 0 == GetWindowRect(geometryAttribute.windowHandle, &oldWindowRect))
			goto call_error;

		if (0 == MoveWindow(
					geometryAttribute.windowHandle,
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
		if (0 == GetWindowRect(geometryAttribute.windowHandle, &windowRect))
			goto call_error;

		if (0 == MoveWindow(
			geometryAttribute.windowHandle,
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
		if (geometryAttribute.hdc == NULL)
		{
			geometryAttribute.hdc = GetDC(geometryAttribute.windowHandle);
			if (geometryAttribute.hdc == NULL)
				throw EasyExcept("System call error!");

			if (0 == SetArcDirection(geometryAttribute.hdc, AD_CLOCKWISE))
				throw EasyExcept("System call error!");
		}

		defaultGeometryAttribute = &geometryAttribute;
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
		if (0 == GetWindowRect(geometryAttribute.windowHandle, &windowRect))
			throw EasyExcept("Get Window Region error!");

		return windowRect;
	}

	////////////////////////////////////////  END  //////////////////////////////////////
}