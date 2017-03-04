#include "easyWindow.h"
#include "easyKeyboard.h"

#include <cassert>

//	pseudo main function used for developers
int main(int argc, wchar_t* argv[]);

///////////////////////////////////////////////////////////////////////////////////

using namespace EasyXPlus;

int WINAPI wWinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	return main(argc, argv);
}