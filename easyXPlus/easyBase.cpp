#include "easyWindow.h"
#include <cassert>

//	pseudo main function used for developers
int main(int argc, wchar_t* argv[]);

///////////////////////////////////////////////////////////////////////////////////

using namespace easyXPlus;

Mouse::EventType convertWinMsgToMouseEventType(UINT msg)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:	return Mouse::EventType::LeftButtonDown;
	case WM_LBUTTONUP:		return Mouse::EventType::LeftButtonUp;
	case WM_RBUTTONDOWN:	return Mouse::EventType::RightButtonDown;
	case WM_RBUTTONUP:		return Mouse::EventType::RightButtonUp;
	case WM_MOUSEMOVE:		return Mouse::EventType::MouseMove;
	default:
		assert(false && "Event type not supported!");
	}
}

LRESULT CALLBACK CustomeWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		{
			Window::EventAttribute* attribute = Window::getDefaultEventAttribute();

			Mouse::EventType eventType = convertWinMsgToMouseEventType(msg);
			Mouse::EventPairs eventPairs = (*attribute)[eventType];

			for (int i = eventPairs.size() - 1; i >= 0; --i)
				(eventPairs[i].first)(eventPairs[i].second);
			return 0;
		}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	return main(argc, argv);
}