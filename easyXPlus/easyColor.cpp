#include "easyColor.h"

namespace easyXPlus
{
	//////////////////////////////////////////////////////////////////////
	//								RGB

	Rgb::Rgb(unsigned char R, unsigned char G, unsigned char B)
	{
		colorValue = RGB(R, G, B);
	}

	/////////////////////////////////////////////////////////////////////

	COLORREF Rgb::toColorref() const
	{
		return colorValue;
	}

	/////////////////////////////////////////////////////////////////////

	Colorable* Rgb::fromColorref(COLORREF colorValue) const
	{
		return new Rgb(
			GetRValue(colorValue),
			GetGValue(colorValue),
			GetBValue(colorValue));
	}

	/////////////////////////////////////////////////////////////////////

	const unsigned char Rgb::getR() const
	{
		return GetRValue(colorValue);
	}

	/////////////////////////////////////////////////////////////////////

	const unsigned char Rgb::getG() const
	{
		return GetGValue(colorValue);
	}

	/////////////////////////////////////////////////////////////////////

	const unsigned char Rgb::getB() const
	{
		return GetBValue(colorValue);
	}

}