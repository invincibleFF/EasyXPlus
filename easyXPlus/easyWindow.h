#ifndef EASY_WINDOW_H
#define EASY_WINDOW_H

#include "easyColor.h"
#include <string>

namespace easyXPlus
{
	class Window
	{
	private:
		friend class Geometry;
		friend class Text;
		struct GeometryAttribute;
		struct TextAttribute;

	public:
		static GeometryAttribute* getDefaultGeometryAttribute();
		static TextAttribute* getDefaultTextAttribute();

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
		void createDC();
		RECT getWindowRect() const;
		void releaseDCResources();
		void releaseGeometryResources();
		void releaseTextResources();

	private:
		struct GeometryAttribute
		{
			GeometryAttribute();
			~GeometryAttribute();

			HDC hdc;
			HPEN pen;			//	created pen, need to delete
			HBRUSH brush;		//	created brush, need to delete
			Rgb dotColor, lineColor, fillColor;	
		};

		struct TextAttribute
		{
			TextAttribute();
			~TextAttribute();

			HDC hdc;
			HFONT font;
			std::wstring fontName;
			bool isBold;
			bool isItalic;
			bool isUnderline;
			unsigned pointSize;	//	todo: test to change default value
			Rgb textColor;
			Rgb bkColor;

			//	Since window handle is created in Outer-Class-Ctor body,
			//	i cannot initialize this member in initialzation lists.
			//	However, i decide to initialize it when setAsDefault() is called.
			void realCtor();

			static void TextAttribute::releaseFont(TextAttribute* attributePtr);
			static void TextAttribute::createFont(TextAttribute* attributePtr);
			static void TextAttribute::applyFont(TextAttribute* attributePtr);
			static void TextAttribute::changeFont(TextAttribute* attributePtr);
		};

	protected:
		static bool registered;
		static GeometryAttribute* defaultGeometryAttribute;
		static TextAttribute* defaultTextAttribute;//	todo:

		static const int INIT_POS_X = 0;
		static const int INIT_POS_Y = 0;
		static const int INIT_WIDTH = 480;
		static const int INIT_HEIGHT = 640;

		HWND windowHandle;
		HDC hdc;
		GeometryAttribute geometryAttribute;
		TextAttribute textAttribute;
	};
}

#endif