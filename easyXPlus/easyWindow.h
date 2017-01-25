#ifndef EASY_WINDOW_H
#define EASY_WINDOW_H

#include "easyColor.h"

namespace easyXPlus
{
	class Window
	{
	public:
		Window();
		Window(unsigned posX, unsigned posY);
		Window(unsigned posX, unsigned posY, unsigned width, unsigned height);

		//	forbit copy constructor
		Window operator = (Window& window) = delete;

		void setBkColor(const Colorable& color);
		const Colorable& getBkColor();

		void resize(unsigned width, unsigned height);
		void reposition(unsigned posX, unsigned posY);
		void setAsDefault();

	private:
		void realCtor(unsigned posX, unsigned posY, unsigned width, unsigned height);

		void registerWindowClass();
		void createWindow(unsigned posX, unsigned posY, unsigned width, unsigned height);

	private:
		static bool registered;

		static const int INIT_POS_X = 0;
		static const int INIT_POS_Y = 0;
		static const int INIT_WIDTH = 480;
		static const int INIT_HEIGHT = 640;

		HWND windowHandle;
		
	};
}

#endif