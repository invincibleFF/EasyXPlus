#ifndef EASY_TEXT_H
#define EASY_TEXT_H

#include "easyGeometry.h"
#include <string>

namespace easyXPlus
{
	//	TODO:
	//		1.add a setFontSize() overload that uses pixel size to set the font.
	//		2.test to see if adding namespace before Rectangle class is useless.
	class Text
	{
	public:
		static void setFont(std::wstring fontName);
		static void setBold(bool isBold);
		static void setItalic(bool isItalic);
		static void setUnderline(bool isUnderline);
		static void setFontSize(unsigned pointSize);
		static void setTextColor(const Colorable& color);
		static void setBkColor(const Colorable& color);

		static std::wstring getCurrentFontName();
		static bool isCurrentBold();
		static bool isCurrentItalic();
		static bool isCurrentUnderline();
		static unsigned getCurrentFontSize();
		static Rgb getCurrentTextColor();
		static Rgb getCurrentBkColor();

		static Rectangle getOutputSize(std::wstring text);
		static void output(const Point pos,  std::wstring text);
	};
}

#endif