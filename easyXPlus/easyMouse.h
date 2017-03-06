#ifndef EASY_MOUSE_H
#define EASY_MOUSE_H

#include "easyGeometry.h"

namespace EasyXPlus
{
	enum class MouseEvent
	{
		None, Move, LeftDown, LeftUp, RightDown, RightUp
	};

	//	TODO:	change Mouse to support multi-window.
	class Mouse
	{
	public:
		static Point getCurrentPos();

		static MouseEvent tryGetEvent();

	private:
		static void pushMouseEvent(UINT msg);
	};
}

#endif