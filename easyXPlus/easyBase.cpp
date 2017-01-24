#include "easyWindow.h"

//	pseudo main function used for developers
extern int main(int argc, wchar_t* argv[]);

///////////////////////////////////////////////////////////////////////////////////

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	BOOL ret = NULL;
	MSG msg;
		
	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	main(argc, argv);

	easyXPlus::Window wind, win;

	while ((ret = GetMessageW(&msg, NULL, 0, 0)) != 0)//	todo: check if non-zero window
	{
		if (ret == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// Return the exit code to the system. 

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		/*{
			int argc = 0;
			LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
		
			main(argc, argv);
			return 0;
		}*/

		default:
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}
}