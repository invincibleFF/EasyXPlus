#ifndef EASY_MOUSE_H
#define EASY_MOUSE_H

#include "easyGeometry.h"

namespace easyXPlus
{
	enum class MouseEvent
	{
		Move, LeftDown, LeftUp, RightDown, RightUp
	};

	//	TODO:	change Mouse to support multi-window.
	class Mouse
	{
	public:
		static Point getCurrentPos();

		static bool hasEvents();
		static MouseEvent getEvent();
	};
}

#endif