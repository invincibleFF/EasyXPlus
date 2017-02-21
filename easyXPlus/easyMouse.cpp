#include "easyMouse.h"
#include "easyWindow.h"
#include "easyExcept.h"
#include <algorithm>

using namespace std;

namespace easyXPlus
{
	//////////////////////////////////////////////////////////////////////////
	//								Mouse class

	Point Mouse::getCurrentPos()
	{
		POINT pos;
		if (0 == GetCursorPos(&pos))
			throw EasyExcept("System call error!");

		if (0 == ScreenToClient(Window::getDefaultWindowHandle(), &pos))
			throw EasyExcept("System call error!");

		return Point(pos.x, pos.y);
	}

	/////////////////////////////////////

	void Mouse::setEventHandler(EventType eventType, EventHandler handler, EventParam param)
	{
		Window::EventAttribute& attribute = *Window::getDefaultEventAttribute();
		attribute[eventType].push_back(make_pair(handler, param));
	}

	////////////////////////////////////

	void Mouse::cancelEventHandler(EventType eventType, EventHandler handler)
	{
		Mouse::EventPairs& eventPairs = (*Window::getDefaultEventAttribute())[eventType];
		auto iterator =
			find_if(eventPairs.begin(), eventPairs.end(), [handler](Mouse::EventPair one)
			{
				return one.first == handler;
			});

		if (iterator == eventPairs.end())
			throw EasyExcept("Handler not found!");
		else
			eventPairs.erase(iterator);
	}
}