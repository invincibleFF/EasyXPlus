#ifndef EASY_WINDOW_H
#define EASY_WINDOW_H

#include "easyColor.h"
#include <string>
#include <utility>	//	for std::pair

namespace easyXPlus
{
	//	TODO:
	//			When a window call setAsDefault() and then is is destructed, the 
	//	defaultWindowHandle variable value is still reserved. But the system may
	//	assign this handle to a different window.
	class Window
	{
	public:
		struct Attribute
		{
			explicit Attribute(HWND handle = NULL)
				:	windowHandle(handle), hdc(NULL), penHandle(NULL), brushHandle(NULL),
					dotColor(Rgb::Red().toColorref()),
					lineColor(Rgb::Black().toColorref()),
					fillColor(Rgb::White().toColorref())
			{}

			HWND windowHandle;
			HDC hdc;
			HPEN penHandle;		//	created pen
			HBRUSH brushHandle;	//	created brush
			COLORREF dotColor;
			COLORREF lineColor;
			COLORREF fillColor;
		};

		static Attribute* getDefaultAttribute();

		Window(const std::wstring title = L"easyX+");
		Window(const std::wstring title, int posX, int posY);
		Window(const std::wstring title, int posX, int posY, unsigned width, unsigned height);

		virtual ~Window();

		//	forbit copy constructor
		Window operator = (Window& window) = delete;

		int getPosX() const;
		int getPosY() const;
		unsigned getWidth() const;
		unsigned getHeight() const;

		void resize(unsigned width, unsigned height);
		void reposition(int posX, int posY);
		void setAsDefault();

		void clear(const Colorable& color);

	private:
		void realCtor(const std::wstring title, int posX, int posY, unsigned width, unsigned height);

		void registerWindowClass();
		void createWindow(const std::wstring title, unsigned posX, unsigned posY, unsigned width, unsigned height);
		RECT getWindowRect() const;

	protected:
		static bool registered;
		static Attribute* defaultAttributePtr;
		
		static const int INIT_POS_X = 0;
		static const int INIT_POS_Y = 0;
		static const int INIT_WIDTH = 480;
		static const int INIT_HEIGHT = 640;

		Attribute attribute;
	};
}

#endif