#include "easyWindow.h"

//	pseudo main function used for developers
extern int main(int argc, wchar_t* argv[]);

///////////////////////////////////////////////////////////////////////////////////

//	custome background color for each window
COLORREF g_bkColor = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{		
	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	return main(argc, argv);
}