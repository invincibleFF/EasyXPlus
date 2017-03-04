#include "easyText.h"
#include "easyWindow.h"
#include "easyExcept.h"
#include "easyColor.h"

using namespace std;

namespace EasyXPlus
{
	///////////////////////////////////////////////////////////////////////////
	//									Macros

#define APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE(oneField)							\
	MultiWindow::TextAttribute* textAttribute = MultiWindow::getDefaultTextAttribute();	\
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
		MultiWindow::TextAttribute* attribute = MultiWindow::getDefaultTextAttribute();
		attribute->textColor = Rgb(color.toColorref());

		if (CLR_INVALID ==
				SetTextColor(attribute->hdc, attribute->textColor.toColorref()))

			throw EasyExcept("System call error!");
	}

	////////////////////////////////////

	void Text::setBkColor(const Colorable& color)
	{
		MultiWindow::TextAttribute* attribute = MultiWindow::getDefaultTextAttribute();
		attribute->bkColor = Rgb(color.toColorref());

		if (CLR_INVALID ==
				SetBkColor(attribute->hdc, attribute->bkColor.toColorref()))

			throw EasyExcept("System call error!");
	}

	////////////////////////////////////

	wstring Text::getCurrentFontName()
	{
		return MultiWindow::getDefaultTextAttribute()->fontName;
	}

	////////////////////////////////////

	bool Text::isCurrentBold()
	{
		return MultiWindow::getDefaultTextAttribute()->isBold;
	}

	///////////////////////////////////

	bool Text::isCurrentItalic()
	{
		return MultiWindow::getDefaultTextAttribute()->isItalic;
	}

	////////////////////////////////////

	bool Text::isCurrentUnderline()
	{
		return MultiWindow::getDefaultTextAttribute()->isUnderline;
	}

	////////////////////////////////////

	unsigned Text::getCurrentFontSize()
	{
		return MultiWindow::getDefaultTextAttribute()->pointSize;
	}

	////////////////////////////////////

	Rgb Text::getCurrentTextColor()
	{
		return MultiWindow::getDefaultTextAttribute()->textColor;
	}

	////////////////////////////////////

	Rgb Text::getCurrentBkColor()
	{
		return MultiWindow::getDefaultTextAttribute()->bkColor;
	}

	////////////////////////////////////

	Rect Text::getOutputSize(std::wstring text)
	{
		MultiWindow::TextAttribute* attribute = MultiWindow::getDefaultTextAttribute();

		SIZE sizeRet;
		BOOL ret = GetTextExtentPoint32W(
			attribute->hdc,
			text.c_str(),
			text.size(),
			&sizeRet);
		if (ret == 0)	throw EasyExcept("System call error!");

		return Rect(sizeRet.cx, sizeRet.cy);
	}

	////////////////////////////////////

	void Text::output(const Point pos, wstring text)
	{
		MultiWindow::TextAttribute* textAttribute = MultiWindow::getDefaultTextAttribute();

		BOOL ret = TextOutW(
			textAttribute->hdc,
			pos.getX(),
			pos.getY(),
			text.c_str(),
			text.size());
		if (ret == 0)	throw EasyExcept("System call error!");
	}

#undef APPLY_ONE_FONT_ATTRIBUTE_FIELD_CHANGE

	///////////////////////////////		END		///////////////////////////////
}