#include "easyText.h"
#include "easyWindow.h"
#include "easyExcept.h"
#include "easyColor.h"

using namespace std;

namespace easyXPlus
{
	///////////////////////////////////////////////////////////////////////////
	//									Macros

#define APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(oneField)							\
	Window::TextAttribute* textAttribute = Window::getDefaultTextAttribute();	\
	textAttribute->oneField = oneField;											\
																				\
	textAttribute->changeFont();

	///////////////////////////////////////////////////////////////////////////
	//									Text

	void Text::setFont(wstring fontName)
	{
		APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(fontName);
	}

	////////////////////////////////////

	void Text::setBold(bool isBold)
	{
		APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(isBold);
	}

	////////////////////////////////////

	void Text::setItalic(bool isItalic)
	{
		APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(isItalic);
	}

	////////////////////////////////////

	void Text::setUnderline(bool isUnderline)
	{
		APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(isUnderline);
	}

	////////////////////////////////////

	void Text::setFontSize(unsigned pointSize)
	{
		APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(pointSize);
	}

	////////////////////////////////////

	void Text::setTextColor(const Colorable& color)
	{
		Window::TextAttribute* attribute = Window::getDefaultTextAttribute();
		attribute->textColor = Rgb(color.toColorref());

		if (CLR_INVALID ==
				SetTextColor(attribute->hdc, attribute->textColor.toColorref()))

			throw EasyExcept("System call error!");
	}

	////////////////////////////////////

	void Text::setBkColor(const Colorable& color)
	{
		Window::TextAttribute* attribute = Window::getDefaultTextAttribute();
		attribute->bkColor = Rgb(color.toColorref());

		if (CLR_INVALID ==
				SetBkColor(attribute->hdc, attribute->bkColor.toColorref()))

			throw EasyExcept("System call error!");
	}

	////////////////////////////////////

	wstring Text::getCurrentFontName()
	{
		return Window::getDefaultTextAttribute()->fontName;
	}

	////////////////////////////////////

	bool Text::isCurrentBold()
	{
		return Window::getDefaultTextAttribute()->isBold;
	}

	///////////////////////////////////

	bool Text::isCurrentItalic()
	{
		return Window::getDefaultTextAttribute()->isItalic;
	}

	////////////////////////////////////

	bool Text::isCurrentUnderline()
	{
		return Window::getDefaultTextAttribute()->isUnderline;
	}

	////////////////////////////////////

	unsigned Text::getCurrentFontSize()
	{
		return Window::getDefaultTextAttribute()->pointSize;
	}

	////////////////////////////////////

	Rgb Text::getCurrentTextColor()
	{
		return Window::getDefaultTextAttribute()->textColor;
	}

	////////////////////////////////////

	Rgb Text::getCurrentBkColor()
	{
		return Window::getDefaultTextAttribute()->bkColor;
	}

	////////////////////////////////////

	Rectangle Text::getOutputSize(std::wstring text)
	{
		Window::TextAttribute* attribute = Window::getDefaultTextAttribute();

		SIZE sizeRet;
		BOOL ret = GetTextExtentPoint32W(
			attribute->hdc,
			text.c_str(),
			text.size(),
			&sizeRet);
		if (ret == 0)	throw EasyExcept("System call error!");

		return Rectangle(sizeRet.cx, sizeRet.cy);
	}

	////////////////////////////////////

	void Text::output(const Point pos, wstring text)
	{
		Window::TextAttribute* textAttribute = Window::getDefaultTextAttribute();

		BOOL ret = TextOutW(
			textAttribute->hdc,
			pos.getX(),
			pos.getY(),
			text.c_str(),
			text.size());
		if (ret == 0)	throw EasyExcept("System call error!");
	}
}