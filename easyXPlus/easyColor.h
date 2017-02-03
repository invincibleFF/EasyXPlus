#ifndef EASY_COLOR_H
#define EASY_COLOR_H

#include <windows.h>

namespace easyXPlus
{
	//	Color Interface definition
	class Colorable
	{
	public:
		virtual COLORREF toColorref() const = 0;
	};

	class Rgb : public Colorable
	{
	public:
		virtual COLORREF toColorref() const;

		Rgb(unsigned char R, unsigned char G, unsigned char B);

		const unsigned char getR() const;
		const unsigned char getG() const;
		const unsigned char getB() const;

		static Rgb Black()		{ return Rgb(0, 0, 0); }
		static Rgb White()		{ return Rgb(255, 255, 255); }
		static Rgb Blue()		{ return Rgb(0, 0, 255); }
		static Rgb Red()		{ return Rgb(255, 0, 0); }
		static Rgb Green()		{ return Rgb(0, 255, 0); }
		static Rgb Grey()		{ return Rgb(190, 190, 190); }
		static Rgb Cyan()		{ return Rgb(0, 255, 255); }
		static Rgb Yellow()		{ return Rgb(255, 255, 0); }
		static Rgb Salmon()		{ return Rgb(250, 128, 114); }
		static Rgb Coral()		{ return Rgb(225, 127, 80); }
		static Rgb Pink()		{ return Rgb(255, 192, 203); }
		static Rgb LightGrey()	{ return Rgb(211, 211, 211); }
		static Rgb LightBlue()	{ return Rgb(173, 216, 230); }
		static Rgb LightCyan()	{ return Rgb(224, 255, 255); }
		static Rgb LightYellow(){ return Rgb(255, 255, 224); }
		static Rgb LightSalmon(){ return Rgb(255, 160, 122); }
		static Rgb LightCoral()	{ return Rgb(240, 128, 128); }
		static Rgb LightPink()	{ return Rgb(255, 182, 193); }
		static Rgb LightGreen()	{ return Rgb(144, 238, 144); }
		//	todo:	dark
		
	protected:
		COLORREF colorValue;
	};
}

#endif