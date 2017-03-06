#include "easyWindow.h"
#include "easyExcept.h"

#include "SU.h"

using namespace EasyXPlus;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//								Tests for ctors and getters

void Init_NotCalled_CallOtherWindowFunctionsThrowExcept()
{
	SU_ASSERT_THROW( Window::resize(90, 90), EasyExcept );
}

void Init_WithPosParams_CreateWindowWithThesePos()
{
	int posX = 234, posY = 245;

	Window::init(L"", posX, posY);

	assert (posX == Window::getPosX());
	assert (posY == Window::getPosY());
}

void Init_WithPosAndWH_CreateWindowWithThesePosAndWH()
{
	int posX = 67, posY = 89;
	unsigned width = 12, height = 567;

	Window::init(L"window", posX, posY, width, height);

	assert (posX == Window::getPosX());
	assert (posY == Window::getPosY());
	assert (width == Window::getWidth());
	assert (height == Window::getHeight());
}

////////////////////////////////////////////////////////////////////////////
//								Tests for Clear

class FakeColor : public Colorable
{
public:
	COLORREF toColorref() const { return RGB(0, 255, 255); }
	Colorable* fromColorref(COLORREF colorValue)const { return new FakeColor(); }
};

////////////////////////////////////////////////////////////////////////////////////////
//								Tests for Resize

void Resize_ByDefault_ResizeToGivenSize()
{
	unsigned width = 567, height = 234;
	Window::init();

	Window::resize(width, height);

	assert (width == Window::getWidth());
	assert(height == Window::getHeight());
}

/////////////////////////////////////////////////////////////////
//					Tests for reposition

void Reposition_ByDefault_RepositionToGivenPos()
{
	int posX = -56, posY = 67;
	Window::init();

	Window::reposition(posX, posY);

	assert (posX == Window::getPosX());
	assert ( posY == Window::getPosY() );
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
	Init_NotCalled_CallOtherWindowFunctionsThrowExcept();
	Text_FunctionCalls_DefaultWindowNotSet_ThrowExcept();

	Window::init();

	Init_WithPosParams_CreateWindowWithThesePos();
	Init_WithPosAndWH_CreateWindowWithThesePosAndWH();
	Resize_ByDefault_ResizeToGivenSize();
	Reposition_ByDefault_RepositionToGivenPos();

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

	MessageBoxW(NULL, L"", L"Succeed!", MB_OK);
	return 0;
}