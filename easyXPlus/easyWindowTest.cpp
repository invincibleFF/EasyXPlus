#include "easyWindow.h"
#include "easyExcept.h"

#include "SU.h"

using namespace easyXPlus;
using namespace std;

/////////////////////////////////////////////////////////////////////////////
//							Faker

class FakeWindow : public Window
{
public:
	FakeWindow(Window window) : Window(window)		{}

	const int getInitPosX() const { return INIT_POS_X; }
	const int getInitPosY() const { return INIT_POS_Y; }
	const int getInitWidth() const { return INIT_WIDTH; }
	const int getInitHeight() const { return INIT_HEIGHT; }
	const bool getRegisteredFlag() const { return registered; }
	const HWND getWindowHandle() const { return windowHandle; }

	const HWND getDefaultWindowHandle() const { return defaultWindowHandle; }

	void resetDefaultWindowHandle() { defaultWindowHandle = NULL; }
	void setWindowHandle(HWND hwnd)	{ windowHandle = hwnd; }
};

////////////////////////////////////////////////////////////////////////////////
//								Tests for ctors and getters

void Ctor_WithZeroParams_CreateWindowWithInitParams()
{
	Window window;
	
	FakeWindow fake(window);
	assert (fake.getInitPosX() == window.getPosX());
	assert (fake.getInitPosY() == window.getPosY());
	assert (fake.getWidth() == window.getWidth());
	assert (fake.getHeight() == window.getHeight());
}

void Ctor_WithPosParams_CreateWindowWithThesePos()
{
	int posX = 234, posY = 245;

	Window window(posX, posY);

	assert (posX == window.getPosX());
	assert (posY == window.getPosY());
}

void Ctor_WithPosAndWH_CreateWindowWithThesePosAndWH()
{
	int posX = 67, posY = 89;
	unsigned width = 12, height = 567;

	Window window(posX, posY, width, height);

	assert (posX == window.getPosX());
	assert (posY == window.getPosY());
	assert (width == window.getWidth());
	assert (height == window.getHeight());
}

void Ctor_ByDefault_NullDefaultHandleAndFalseRegisteredFlag()
{
	FakeWindow(Window()).resetDefaultWindowHandle();

	Window window;
	FakeWindow fake(window);

	assert (true == fake.getRegisteredFlag());
	assert (NULL == (INT)fake.getDefaultWindowHandle());
}

////////////////////////////////////////////////////////////////////////////
//								Tests for Clear

class FakeColor : public Colorable
{
public:
	COLORREF toColorref() const { return RGB(0, 255, 255); }
};

void Clear_ByDefault_ClearToColorGiven()
{
	Window window(120, 400, 90, 90);
	FakeWindow fakeWindow(window);

	fakeWindow.clear(FakeColor());

	assert(	FakeColor().toColorref()
				==
			GetPixel(GetDC(fakeWindow.getWindowHandle()), 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////
//								Tests for Resize

void Resize_ByDefault_ResizeToGivenSize()
{
	unsigned width = 567, height = 234;
	Window window;

	window.resize(width, height);

	assert (width == window.getWidth());
	assert(height == window.getHeight());
}

void Resize_NullHandle_ThrowException()
{
	FakeWindow fake(Window{});
	fake.setWindowHandle(NULL);

	SU_THROW(fake.resize(12, 34), EasyExcept);
}

/////////////////////////////////////////////////////////////////
//					Tests for reposition

void Reposition_ByDefault_RepositionToGivenPos()
{
	int posX = -56, posY = 67;
	Window window;

	window.reposition(posX, posY);

	assert (posX == window.getPosX());
	assert ( posY == window.getPosY() );
}

void Reposiion_NullHandle_ThrowException()
{
	FakeWindow fakeWindow(Window{12,12, 120, 120});
	fakeWindow.setWindowHandle(NULL);

	SU_THROW( fakeWindow.reposition(34, 34), EasyExcept);
}

////////////////////////////////////////////////////////////////////////////
//						Tests for setAsDefault

void SetAsDefault_ByDefault_SetDefultWindowHandleToThis()
{
	Window window;

	window.setAsDefault();
	
	FakeWindow fake(window);
	assert(fake.getWindowHandle() == fake.getDefaultWindowHandle());
}

//////////////////////////////////////////////////////////////////////////////

//	tests in other units
void Ctor_ByDefault_ConstructColorValue();
void Getters_ByDefault_GetRGBValue();

int main(int argc, wchar_t* argv[])
{
	Ctor_WithZeroParams_CreateWindowWithInitParams();
	Ctor_WithPosParams_CreateWindowWithThesePos();
	Ctor_WithPosAndWH_CreateWindowWithThesePosAndWH();
	Ctor_ByDefault_NullDefaultHandleAndFalseRegisteredFlag();

	Clear_ByDefault_ClearToColorGiven();

	Resize_ByDefault_ResizeToGivenSize();
	Resize_NullHandle_ThrowException();

	Reposition_ByDefault_RepositionToGivenPos();
	Reposiion_NullHandle_ThrowException();

	SetAsDefault_ByDefault_SetDefultWindowHandleToThis();

	///////////////			Colorable		//////////////////

	Ctor_ByDefault_ConstructColorValue();
	Getters_ByDefault_GetRGBValue();

	return 0;
}