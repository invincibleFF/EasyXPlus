#include "easyWindow.h"

//	pseudo main function used for developers
extern int main(int argc, wchar_t* argv[]);

///////////////////////////////////////////////////////////////////////////////////

//	custome background color for each window
COLORREF g_bkColor = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_ERASEBKGND)
	{
		if (g_bkColor != NULL)
		{
			SetBkColor((HDC)wParam, g_bkColor);
			return true;
		}
		return 0;
	}
		

	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{		
	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	return main(argc, argv);
}

///////////////////////////////////////////////////////////////////////////////
//			test code

class COLOR : public easyXPlus::Colorable
{
public:
	virtual COLORREF toColorref() const { return RGB(255,255,255); }
};

int main(int argc, wchar_t* argv[])
{
	easyXPlus::Window window;
	window.resize(400, 20);
	window.reposition(20, 20);

	return 0;
}