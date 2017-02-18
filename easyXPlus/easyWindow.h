#ifndef EASY_WINDOW_H
#define EASY_WINDOW_H

#include "easyColor.h"
#include <string>

namespace easyXPlus
{
	//	TODO:
	//			When a window call setAsDefault() and then is is destructed, the 
	//	defaultWindowHandle variable value is still reserved. But the system may
	//	assign this handle to a different window.
	class Window
	{
	private:
		friend class Geometry;
		struct GeometryAttribute;
		struct TextAttribute;

	public:
		static GeometryAttribute* getDefaultGeometryAttribute();
		static TextAttribute* getDefaultTextAttribute();//	todo:

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
		void releaseGeometryResources();

	private:
		struct GeometryAttribute
		{
			explicit GeometryAttribute(HWND handle = NULL)
				:	windowHandle(handle), 
					hdc(NULL), pen(NULL), brush(NULL),
					dotColor(Rgb::Red()), lineColor(Rgb::Black()), fillColor(Rgb::White())
			{}

			HWND windowHandle;
			HDC hdc;			//	created dc, need to delete
			HPEN pen;			//	created pen, need to delete
			HBRUSH brush;		//	created brush, need to delete
			Rgb dotColor, lineColor, fillColor;	
		};

		struct TextAttribute
		{
			//	todo:
		};

	protected:
		static bool registered;
		static GeometryAttribute* defaultGeometryAttribute;
		static TextAttribute* defaultTextAttribute;//	todo:

		static const int INIT_POS_X = 0;
		static const int INIT_POS_Y = 0;
		static const int INIT_WIDTH = 480;
		static const int INIT_HEIGHT = 640;

		GeometryAttribute geometryAttribute;
		TextAttribute textAttribute;
	};
}

#endif