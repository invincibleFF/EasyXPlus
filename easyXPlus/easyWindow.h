#ifndef EASY_WINDOW_H
#define EASY_WINDOW_H

#include "easyColor.h"

namespace easyXPlus
{
	class Window
	{
	public:
		Window();
		Window(int posX, int posY);
		Window(int posX, int posY, unsigned width, unsigned height);

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
		void realCtor(int posX, int posY, unsigned width, unsigned height);

		void registerWindowClass();
		void createWindow(unsigned posX, unsigned posY, unsigned width, unsigned height);
		RECT getWindowRect() const;

	protected:
		static bool registered;
		static HWND defaultWindowHandle;

		static const int INIT_POS_X = 0;
		static const int INIT_POS_Y = 0;
		static const int INIT_WIDTH = 480;
		static const int INIT_HEIGHT = 640;

		HWND windowHandle;
	};
}

#endif