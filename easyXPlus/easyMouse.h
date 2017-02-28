#ifndef EASY_MOUSE_H
#define EASY_MOUSE_H

#include "easyGeometry.h"

namespace easyXPlus
{
	enum class MouseEvent
	{
		None, Move, LeftDown, LeftUp, RightDown, RightUp
	};

	class Mouse
	{
	public:
		static Point getCurrentPos();
		static MouseEvent tryGetEvent();
	};
}

#endif