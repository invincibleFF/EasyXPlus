#ifndef EASY_MOUSE_H
#define EASY_MOUSE_H

#include "easyGeometry.h"

namespace easyXPlus
{
	class Mouse
	{
	public:
		enum class EventType
		{
			LeftButtonDown,		LeftButtonUp,
			RightButtonDown,	RightButtonUp,
			MouseMove
		};

		typedef void*				EventParam;
		typedef void(*EventHandler)(EventParam paramater);
		typedef std::pair<EventHandler, EventParam>	EventPair;
		typedef std::vector<EventPair>				EventPairs;

		static Point getCurrentPos();
		static void setEventHandler(
			EventType eventType, EventHandler handler, EventParam paramToPass);
		static void cancelEventHandler(
			EventType eventType, EventHandler handler);
	};
}

#endif