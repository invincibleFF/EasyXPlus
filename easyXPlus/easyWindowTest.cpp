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
	FakeWindow(Window& window) : Window(window)		{}
	~FakeWindow()
	{ 
		hdc = NULL; geometryAttribute.brush = NULL;
		geometryAttribute.pen = NULL; textAttribute.font = NULL;
	}

	const int getInitPosX() const { return INIT_POS_X; }
	const int getInitPosY() const { return INIT_POS_Y; }
	const int getInitWidth() const { return INIT_WIDTH; }
	const int getInitHeight() const { return INIT_HEIGHT; }
	const bool getRegisteredFlag() const { return registered; }
	const HWND getWindowHandle() const { return windowHandle; }
	const void* getTextAttribute() const { return &textAttribute; }
	const void* getGeometryAttribute() const { return &geometryAttribute; }


	void resetDefaultGeometryAttribute() { defaultGeometryAttribute = nullptr; }
	void resetDefaultTextAttribute() { defaultTextAttribute = nullptr; }
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

	Window window(L"window", posX, posY);

	assert (posX == window.getPosX());
	assert (posY == window.getPosY());
}

void Ctor_WithPosAndWH_CreateWindowWithThesePosAndWH()
{
	int posX = 67, posY = 89;
	unsigned width = 12, height = 567;

	Window window(L"window", posX, posY, width, height);

	assert (posX == window.getPosX());
	assert (posY == window.getPosY());
	assert (width == window.getWidth());
	assert (height == window.getHeight());
}

void Ctor_ByDefault_NullDefaultAttributesAndFalseRegisteredFlag()
{
	FakeWindow(Window()).resetDefaultGeometryAttribute();

	Window window;
	FakeWindow fake(window);

	assert (true == fake.getRegisteredFlag());
	SU_ASSERT_THROW (fake.getDefaultGeometryAttribute(), EasyExcept);
	SU_ASSERT_THROW(fake.getDefaultTextAttribute(), EasyExcept);
}

////////////////////////////////////////////////////////////////////////////
//								Tests for Clear

class FakeColor : public Colorable
{
public:
	COLORREF toColorref() const { return RGB(0, 255, 255); }
	Colorable* fromColorref(COLORREF colorValue)const { return new FakeColor(); }
};

void Clear_ByDefault_ClearToColorGiven()
{
	Window window(L"window", 120, 400, 90, 90);
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
	HWND oldHandle = fake.getWindowHandle();
	fake.setWindowHandle(NULL);

	SU_ASSERT_THROW(fake.resize(12, 34), EasyExcept);

	//	to make destructer pass
	fake.setWindowHandle(oldHandle);
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
	FakeWindow fakeWindow(Window{ L"window", 12, 12, 120, 120 });
	HWND oldHandle = fakeWindow.getWindowHandle();
	fakeWindow.setWindowHandle(NULL);

	SU_ASSERT_THROW( fakeWindow.reposition(34, 34), EasyExcept);

	fakeWindow.setWindowHandle(oldHandle);
}

////////////////////////////////////////////////////////////////////////////
//						Tests for setAsDefault

void SetAsDefault_ByDefault_SetDefultAttributes()
{
	FakeWindow fake(Window{});
	fake.setAsDefault();

	assert(fake.getDefaultTextAttribute() == fake.getTextAttribute());
	assert(fake.getDefaultGeometryAttribute() == fake.getGeometryAttribute());
}

/////////////////////////////////////////////////////////////////////////////
//						Tests for Window::getDefaultWindowHandle

void GetDefaultGeometryAttribute_NotSet_ThrowExcept()
{
	Window window;
	FakeWindow fakeWindow(window);

	fakeWindow.resetDefaultGeometryAttribute();

	SU_ASSERT_THROW(Window::getDefaultGeometryAttribute(), EasyExcept);
}

void GetDefaultTextAttribute_NotSet_ThrowExcept()
{
	Window window;
	FakeWindow fakeWindow(window);

	fakeWindow.resetDefaultGeometryAttribute();

	SU_ASSERT_THROW(Window::getDefaultGeometryAttribute(), EasyExcept);
}

//////////////////////////////////////////////////////////////////////////////

//	tests in other units
void Ctor_ByDefault_ConstructColorValue();
void Getters_ByDefault_GetRGBValue();

void RectRegion_Ctor_InvalidRectRegion_ThrowExcept();

void PointArray_GetPoint_InvalidIndex_ThrowExcept();
void PointArray_InsertPoint_InvalidIndex_ThrowExcept();

void Geometry_SetDotColor_ByDefault_DrawDotWithThisColor();
void Geometry_SetLineColor_ByDefault_DrawLineWithThisColor();
void Geometry_SetLineColor_SameColor_ColorNotChange();
void Geometry_SetFillColor_ByDefault_DrawShapesWithThisColor();
void Geometry_SetFillColor_SameColor_ColorNotChange();
void Geometry_SetColors_DifferentWindow_KeepFormerColorSettings();
void Geometry_Drawers_ByDefault_SeeWindowOutput();
void Geometry_DrawDot_ByDefault_DrawDotWithDotColor();
void Geometry_DrawLine_AfterDraw_DotColorAndLineColorNotChange();
void Geometry_DrawLine_ByDefault_IncludeTwoEndPoint();
void Geometry_DrawLine_TwoSameEnd_DrawOnePoint();
void Geometry_DrawArc_SameStartAndEndPoint_DrawEntireEllipse();
void Geometry_DrawArc_TwoPointsOneCenterOneNot_ThrowExcep();
void Geometry_DrawBezier_PointNumberNotThreeTimePlusOne_ThrowExcept();
void Geometry_DrawBezier_ByDefault_IncludeTwoEndAndTwoControlPoints();
void Geometry_DrawPolyline_ByDefault_IncludeAllStartAndEndsPoints();
void Geometry_DrawPolyline_PointNumberNotGreaterOne_ThrowExcept();
void Geometry_DrawChord_EndPointsOneCenterAnotherNot_ThrowExcept();
void Geometry_DrawRectangle_ByDegault_IncludeBottomLineAndRightLine();
void Geometry_DrawPie_TwoEndsOneCanterOneAnoter_ThrowExcept();
void Geometry_DrawPolygon_PointNumberLessThree_ThrowExcept();

void Text_FunctionCalls_DefaultWindowNotSet_ThrowExcept();
void Text_SetFont_ByDefault_GetWhatSet();
void Text_SetBold_ByDefault_GetWhatSet();
void Text_SetItalic_ByDefault_GetWhatSet();
void Text_SetUnderline_ByDefault_GetWhatSet();
void Text_SetFontSize_ByDefault_GetWhatSet();
void Text_SetTextColor_ByDefault_GetWhatSet();
void Text_SetBkColor_ByDefault_GetWhatSet();

void GetCurrentPos_ByDefault_GetWhereItIs();
void TryGetEvent_NoEvent_ReturnNone();
void TryGetEvent_SupportedEvent_ReturnEvent();
void TryGetEvent_NotSupportedEvent_ReturnNone();
void TryGetEvent_SupportedMixedWithUnsupported_ReturnSupported();

/*
	uncomment to run the test
	void IsPressed_ByDefault_CanDetected();
*/

void TryGetPressed_NoPressed_ReturnKeyNone();
void TryGetPressed_SupportedKeyPressed_ReturnKey();
void TryGetPressed_ManyKeyDownOneKeyUp_MiddleMsgsIgnored();
void TryGetPressed_KeyMsgsAfterCharMsgs_ReturnKey();
void TryGetPressed_KeyMsgsBeforeCharMsgs_ReturnKey();
void TryGetPressed_OnlyKeyDownMsg_ReturnKeyNone();
void TryGetPressed_TwoKeyPressed_GetTwo();

void PauseAll_PassZero_ThrowExcept();

//////////////////////////////////////////////////////////////////////

int main(int argc, wchar_t* argv[])
{
	Ctor_WithZeroParams_CreateWindowWithInitParams();
	Ctor_WithPosParams_CreateWindowWithThesePos();
	Ctor_WithPosAndWH_CreateWindowWithThesePosAndWH();
	Ctor_ByDefault_NullDefaultAttributesAndFalseRegisteredFlag();

	Clear_ByDefault_ClearToColorGiven();

	Resize_ByDefault_ResizeToGivenSize();
	Resize_NullHandle_ThrowException();

	Reposition_ByDefault_RepositionToGivenPos();
	Reposiion_NullHandle_ThrowException();

	SetAsDefault_ByDefault_SetDefultAttributes();
	GetDefaultGeometryAttribute_NotSet_ThrowExcept();

	///////////////			Colorable		//////////////////

	Ctor_ByDefault_ConstructColorValue();
	Getters_ByDefault_GetRGBValue();

	///////////////			Geometry		//////////////////

	RectRegion_Ctor_InvalidRectRegion_ThrowExcept();

	PointArray_GetPoint_InvalidIndex_ThrowExcept();
	PointArray_InsertPoint_InvalidIndex_ThrowExcept();

	Geometry_SetDotColor_ByDefault_DrawDotWithThisColor();
	Geometry_SetLineColor_ByDefault_DrawLineWithThisColor();
	Geometry_SetLineColor_SameColor_ColorNotChange();
	Geometry_SetFillColor_ByDefault_DrawShapesWithThisColor();
	Geometry_SetFillColor_SameColor_ColorNotChange();
	Geometry_SetColors_DifferentWindow_KeepFormerColorSettings();
	Geometry_DrawDot_ByDefault_DrawDotWithDotColor();
	Geometry_DrawLine_AfterDraw_DotColorAndLineColorNotChange();
	Geometry_DrawLine_ByDefault_IncludeTwoEndPoint();
	Geometry_DrawLine_TwoSameEnd_DrawOnePoint();
	Geometry_DrawArc_SameStartAndEndPoint_DrawEntireEllipse();
	Geometry_DrawArc_TwoPointsOneCenterOneNot_ThrowExcep();
	Geometry_DrawBezier_PointNumberNotThreeTimePlusOne_ThrowExcept();
	Geometry_DrawBezier_ByDefault_IncludeTwoEndAndTwoControlPoints();
	Geometry_DrawPolyline_ByDefault_IncludeAllStartAndEndsPoints();
	Geometry_DrawPolyline_PointNumberNotGreaterOne_ThrowExcept();
	Geometry_DrawChord_EndPointsOneCenterAnotherNot_ThrowExcept();
	Geometry_DrawRectangle_ByDegault_IncludeBottomLineAndRightLine();
	Geometry_DrawPie_TwoEndsOneCanterOneAnoter_ThrowExcept();
	Geometry_DrawPolygon_PointNumberLessThree_ThrowExcept();

	////////////////////		Text		/////////////////////

	Text_FunctionCalls_DefaultWindowNotSet_ThrowExcept();
	Text_SetFont_ByDefault_GetWhatSet();
	Text_SetBold_ByDefault_GetWhatSet();
	Text_SetItalic_ByDefault_GetWhatSet();
	Text_SetUnderline_ByDefault_GetWhatSet();
	Text_SetFontSize_ByDefault_GetWhatSet();
	Text_SetTextColor_ByDefault_GetWhatSet();
	Text_SetBkColor_ByDefault_GetWhatSet();

	/////////////////////		Mouse		////////////////////////

	GetCurrentPos_ByDefault_GetWhereItIs();
	TryGetEvent_NoEvent_ReturnNone();
	TryGetEvent_SupportedEvent_ReturnEvent();
	TryGetEvent_NotSupportedEvent_ReturnNone();
	TryGetEvent_SupportedMixedWithUnsupported_ReturnSupported();

	////////////////////////	Keyboard	////////////////////////

	/*	
		uncomment to run the test
		IsPressed_ByDefault_CanDetected();
	*/
	TryGetPressed_NoPressed_ReturnKeyNone();
	TryGetPressed_SupportedKeyPressed_ReturnKey();
	TryGetPressed_ManyKeyDownOneKeyUp_MiddleMsgsIgnored();
	TryGetPressed_KeyMsgsAfterCharMsgs_ReturnKey();
	TryGetPressed_KeyMsgsBeforeCharMsgs_ReturnKey();
	TryGetPressed_OnlyKeyDownMsg_ReturnKeyNone();
	TryGetPressed_TwoKeyPressed_GetTwo();

	//////////////////////		Others		/////////////////////////

	PauseAll_PassZero_ThrowExcept();

	return 0;
}