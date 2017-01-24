#ifndef EASY_COLOR_H
#define EASY_COLOR_H

#include <windows.h>

namespace easyXPlus
{
	//	Color Interface definition
	class Colorable
	{
	public:
		virtual COLORREF toColorref() = 0;
	};
}

#endif