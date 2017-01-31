#include "CppUnitTest.h"

#include "../easyXPlus/easyWindow.cpp"
#include "../easyXPlus/easyBase.cpp"

using namespace easyXPlus;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
};

namespace easyXPlusTest
{		
	TEST_CLASS(EasyWindow)
	{
	public:
		
		TEST_METHOD(Ctor_WithZeroParams_CreateWindowWithInitParams)
		{
			Window window;
			FakeWindow fake(window);

			Assert::AreEqual(fake.getInitPosX(), window.getPosX());
			Assert::AreEqual(fake.getInitPosY(), window.getPosY());
			Assert::AreEqual(fake.getWidth(), window.getWidth());
			Assert::AreEqual(fake.getHeight(), window.getHeight());
		}

		TEST_METHOD(Ctor_WithPosParams_CreateWindowWithThesePos)
		{
			unsigned posX = 234, posY = 245;
			Window window(posX, posY);

			Assert::AreEqual(static_cast<int>(posX), window.getPosX());
			Assert::AreEqual(static_cast<int>(posY), window.getPosY());
		}

		TEST_METHOD(Ctor_WithPosAndWH_CreateWindowWithThesePosAndWH)
		{
			unsigned posX = 67, posY = 89;
			unsigned width = 12, height = 567;
			Window window(posX, posY, width, height);

			Assert::AreEqual(static_cast<int>(posX), window.getPosX());
			Assert::AreEqual(static_cast<int>(posY), window.getPosY());
			Assert::AreEqual(width, window.getWidth());
			Assert::AreEqual(height, window.getHeight());
		}

#error "test exceptions"
	};
}