#include "easyBaseWindow.h"
#include "easyKeyboard.h"
#include "easyExcept.h"

#include <cassert>

//	pseudo main function used for developers
int main(int argc, wchar_t* argv[]);

///////////////////////////////////////////////////////////////////////////////////

using namespace EasyXPlus;

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	BaseWindow window;
	window.setAsDefault();

	MSG msg;
	BOOL fGotMessage;
	while ((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0 && fGotMessage != -1)
	{
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

DWORD WINAPI MainThread(LPVOID param)
{
	if (0 == SetThreadPriority(
		GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN))
		throw EasyExcept("Thread priority set error!");

	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	return main(argc, argv);
}

LRESULT CALLBACK EasyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		{
			static bool called = false;

			if (!called)
			{
				if (NULL == CreateThread(NULL, NULL, MainThread, nullptr, 0, NULL))
					throw EasyExcept("Thread create error!");
				called = true;
			}
			return 0;
		}

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:

	default:
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
}