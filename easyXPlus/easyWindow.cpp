#include "easyWindow.h"
#include "easyExcept.h"

#include <cassert>

using namespace std;

namespace EasyXPlus
{
	/////////////////////////////////////////////////////////////////////////////////////
	//								Static MultiWindow variables

	bool MultiWindow::registered = false;
	HWND MultiWindow::defaultWindowHandle = NULL;
	MultiWindow::TextAttribute* MultiWindow::defaultTextAttribute = nullptr;
	MultiWindow::GeometryAttribute* MultiWindow::defaultGeometryAttribute = nullptr;

	/////////////////////////////////////////////////////////////////////////////////////
	//								Static MultiWindow functions

	HWND MultiWindow::getDefaultWindowHandle()
	{
		if (defaultWindowHandle == NULL)
			throw EasyExcept("No default window set!");

		return defaultWindowHandle;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	MultiWindow::TextAttribute* MultiWindow::getDefaultTextAttribute()
	{
		if (defaultTextAttribute == nullptr)
			throw EasyExcept("No default window set!");

		return defaultTextAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	MultiWindow::GeometryAttribute* MultiWindow::getDefaultGeometryAttribute()
	{
		if (defaultGeometryAttribute == nullptr)
			throw EasyExcept("No default window set!");

		return defaultGeometryAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//									MultiWindow class

	MultiWindow::MultiWindow(const wstring title)
	{
		realCtor(title, INIT_POS_X, INIT_POS_Y, INIT_WIDTH, INIT_HEIGHT);
	}

	MultiWindow::MultiWindow(const wstring title, int posX, int posY)
	{
		realCtor(title, posX, posY, INIT_WIDTH, INIT_HEIGHT);
	}

	MultiWindow::MultiWindow(const wstring title, int posX, int posY, unsigned width, unsigned height)
	{
		realCtor(title, posX, posY, width, height);
	}

	MultiWindow::~MultiWindow()
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
	}

	///////////////////////////////////////

	void MultiWindow::realCtor(const wstring title, int posX, int posY, unsigned width, unsigned height)
	{
		registerWindowClass();
		createWindow(title.c_str(), posX, posY, width, height);
		createDC();
		ShowWindow(windowHandle, SW_SHOW);
		UpdateWindow(windowHandle); 
	}

	void MultiWindow::registerWindowClass()
	{
		if (!registered)
		{
			WNDCLASSW wndclass = { 0 };
			wndclass.lpszClassName = L"EasyXPlus::WindowClassName";
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

	void MultiWindow::createWindow(const wstring title, unsigned posX, unsigned posY, unsigned width, unsigned height)
	{
		windowHandle = CreateWindowW(
			L"EasyXPlus::WindowClassName",
			title.c_str(),
			WS_POPUP,
			posX, posY,
			width, height,
			NULL, NULL,
			NULL, NULL);

		if (windowHandle == NULL)
			throw EasyExcept("Cannot create window!");
	}

	void MultiWindow::createDC()
	{
		if (NULL == (hdc = GetDC(windowHandle)))
			throw EasyExcept("System call error!");

		geometryAttribute.hdc = textAttribute.hdc = hdc;
		textAttribute.realCtor();

		if (0 == SetArcDirection(geometryAttribute.hdc, AD_CLOCKWISE))
			throw EasyExcept("System call error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void MultiWindow::clear(const Colorable& color)
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
		throw EasyExcept("MultiWindow clear error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void MultiWindow::resize(unsigned width, unsigned height)
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
		throw EasyXPlus::EasyExcept("resize error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void MultiWindow::reposition(int posX, int posY)
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
		throw EasyXPlus::EasyExcept("reposition error!");
	}

	/////////////////////////////////////////////////////////////////////////////////////

	void MultiWindow::setAsDefault()
	{
		defaultWindowHandle=  windowHandle;
		defaultGeometryAttribute = &geometryAttribute;
		defaultTextAttribute = &textAttribute;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	int MultiWindow::getPosX() const
	{
		return getWindowRect().left;
	}

	int MultiWindow::getPosY() const
	{
		return getWindowRect().top;
	}

	unsigned MultiWindow::getWidth() const
	{
		RECT rect = getWindowRect();
		return rect.right - rect.left;
	}

	unsigned MultiWindow::getHeight() const
	{
		RECT rect = getWindowRect();
		return rect.bottom - rect.top;
	}

	RECT MultiWindow::getWindowRect() const
	{
		RECT windowRect;
		if (0 == GetWindowRect(windowHandle, &windowRect))
			throw EasyExcept("Get MultiWindow Region error!");

		return windowRect;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//								GeometryAttribute struct

	MultiWindow::GeometryAttribute::GeometryAttribute() :
		hdc(NULL), pen(NULL), brush(NULL),
		dotColor(Rgb::Red()), lineColor(Rgb::Black()), fillColor(Rgb::White())
	{}

	MultiWindow::GeometryAttribute::~GeometryAttribute()
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

	MultiWindow::TextAttribute::TextAttribute() :
		hdc(NULL),
		fontName(L"Arial"), isBold(false), isItalic(false), isUnderline(false),
		pointSize(14), textColor(Rgb::White()), bkColor(Rgb::Black())
	{
	}

	MultiWindow::TextAttribute::~TextAttribute()
	{
		if (font != NULL)
			if (0 == DeleteObject((HGDIOBJ)font))
				throw EasyExcept("System call error!");
	}

	////////////////////////////////

	void MultiWindow::TextAttribute::realCtor()
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

	void MultiWindow::TextAttribute::releaseFont()
	{
		if (0 == DeleteObject(font))
			throw EasyExcept("System call error!");
	}

	/////////////////////////////////

	void MultiWindow::TextAttribute::createFont()
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

	void MultiWindow::TextAttribute::applyFont()
	{
		if (NULL == SelectObject(hdc, font))
			throw EasyExcept("System call error!");
	}

	//////////////////////////////////////

	void MultiWindow::TextAttribute::changeFont()
	{
		TextAttribute::releaseFont();
		TextAttribute::createFont();
		TextAttribute::applyFont();
	}

	////////////////////////////////////////  END  //////////////////////////////////////
}