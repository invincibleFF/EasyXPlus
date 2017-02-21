#include "easyWindow.h"
#include "easyExcept.h"

#include <cassert>

using namespace std;

extern LRESULT CALLBACK CustomeWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace easyXPlus
{
	/////////////////////////////////////////////////////////////////////////////////////
	//								Static Window variables

	bool Window::registered = false;
	HWND Window::defaultWindowHandle = NULL;
	Window::TextAttribute* Window::defaultTextAttribute = nullptr;
	Window::GeometryAttribute* Window::defaultGeometryAttribute = nullptr;
	Window::EventAttribute* Window::defaultEventAttribute = nullptr;

	/////////////////////////////////////////////////////////////////////////////////////
	//								Static Window functions

	HWND Window::getDefaultWindowHandle()
	{
		if (defaultWindowHandle == NULL)
			throw EasyExcept("No default window set!");

		return defaultWindowHandle;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	Window::TextAttribute* Window::getDefaultTextAttribute()
	{
		if (defaultTextAttribute == nullptr)
			throw EasyExcept("No default window set!");

		return defaultTextAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	Window::GeometryAttribute* Window::getDefaultGeometryAttribute()
	{
		if (defaultGeometryAttribute == nullptr)
			throw EasyExcept("No default window set!");

		return defaultGeometryAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	Window::EventAttribute* Window::getDefaultEventAttribute()
	{
		if (defaultEventAttribute == nullptr)
			throw EasyExcept("No default window set!");

		return defaultEventAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//									Window class

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
		if (hdc != NULL)
			if (0 == ReleaseDC(windowHandle, hdc))
				throw EasyExcept("System call error!");

		if (defaultWindowHandle = defaultWindowHandle)
			defaultWindowHandle = NULL;
		if (defaultGeometryAttribute ==  &geometryAttribute)
			defaultGeometryAttribute = nullptr;
		if (defaultTextAttribute == &textAttribute)
			defaultTextAttribute = nullptr;
		if (defaultEventAttribute == &eventAttribute)
			defaultEventAttribute = nullptr;
	}

	///////////////////////////////////////

	void Window::realCtor(const wstring title, int posX, int posY, unsigned width, unsigned height)
	{
		registerWindowClass();
		createWindow(title.c_str(), posX, posY, width, height);
		createDC();
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
			wndclass.lpfnWndProc = CustomeWndProc;					//	default window procedure
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
		windowHandle = CreateWindowW(
			L"easyXPlus::WindowClassName",
			title.c_str(),
			WS_POPUP | WS_CAPTION,
			posX, posY,
			width, height,
			NULL, NULL,
			NULL, NULL);

		if (windowHandle == NULL)
			throw EasyExcept("Cannot create window!");
	}

	void Window::createDC()
	{
		if (NULL == (hdc = GetDC(windowHandle)))
			throw EasyExcept("System call error!");

		geometryAttribute.hdc = textAttribute.hdc = hdc;
		textAttribute.realCtor();

		if (0 == SetArcDirection(geometryAttribute.hdc, AD_CLOCKWISE))
			throw EasyExcept("System call error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void Window::clear(const Colorable& color)
	{
		HBRUSH brush = CreateSolidBrush(color.toColorref());
		if (brush == NULL)
			goto error;

		RECT clientRect;
		if (0 == GetClientRect(windowHandle, &clientRect))
			goto error;
		
		if (!FillRect(GetDC(windowHandle), &clientRect, brush))
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

	void Window::reposition(int posX, int posY)
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
		defaultWindowHandle=  windowHandle;
		defaultGeometryAttribute = &geometryAttribute;
		defaultTextAttribute = &textAttribute;
		defaultEventAttribute = &eventAttribute;
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

	/////////////////////////////////////////////////////////////////////////////////////
	//								GeometryAttribute struct

	Window::GeometryAttribute::GeometryAttribute() :
		hdc(NULL), pen(NULL), brush(NULL),
		dotColor(Rgb::Red()), lineColor(Rgb::Black()), fillColor(Rgb::White())
	{}

	Window::GeometryAttribute::~GeometryAttribute()
	{
		if (pen != NULL)
			if (0 == DeleteObject((HGDIOBJ)pen))
				throw EasyExcept("System call error!");
		if (brush != NULL)
			if (0 == DeleteObject((HGDIOBJ)brush))
				throw EasyExcept("System call error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//								TextAttribute struct

	Window::TextAttribute::TextAttribute() :
		hdc(NULL),
		fontName(L"Arial"), isBold(false), isItalic(false), isUnderline(false),
		pointSize(70), textColor(Rgb::White()), bkColor(Rgb::Black())
	{
	}

	Window::TextAttribute::~TextAttribute()
	{
		if (font != NULL)
			if (0 == DeleteObject((HGDIOBJ)font))
				throw EasyExcept("System call error!");
	}

	////////////////////////////////

	void Window::TextAttribute::realCtor()
	{
		createFont();

		if (NULL == SelectObject(hdc, font))
			throw EasyExcept("System call error!");
		if (CLR_INVALID == SetTextColor(hdc, textColor.toColorref()))
			throw EasyExcept("System call error!");
		if (CLR_INVALID == SetBkColor(hdc, bkColor.toColorref()))
			throw EasyExcept("System call error!");
	}

	////////////////////////////////////////////////////////////////////
	//					static TextAttribute functions

	void Window::TextAttribute::releaseFont()
	{
		if (0 == DeleteObject(font))
			throw EasyExcept("System call error!");
	}

	/////////////////////////////////

	void Window::TextAttribute::createFont()
	{
		font = CreateFont(
			-MulDiv(pointSize, GetDeviceCaps(hdc, LOGPIXELSY), 72),
			0, 0, 0,
			isBold ? FW_BOLD : FW_NORMAL,
			isItalic,
			isUnderline,
			FALSE,
			CHINESEBIG5_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			CLEARTYPE_QUALITY,
			DEFAULT_PITCH,
			fontName.c_str());
		if (font == NULL)	throw EasyExcept("System call error!");
	}

	///////////////////////////////////////

	void Window::TextAttribute::applyFont()
	{
		if (NULL == SelectObject(hdc, font))
			throw EasyExcept("System call error!");
	}

	//////////////////////////////////////

	void Window::TextAttribute::changeFont()
	{
		TextAttribute::releaseFont();
		TextAttribute::createFont();
		TextAttribute::applyFont();
	}

	////////////////////////////////////////  END  //////////////////////////////////////
}