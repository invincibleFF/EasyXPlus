#include "easyGeometry.h"
#include "easyWindow.h"
#include "easyColor.h"
#include "easyExcept.h"

#include "SU.h"

#include <string>

using namespace std;
using namespace easyXPlus;

////////////////////////////////////////////////////////////////////////////
//							Tests for PointArray

void RectRegion_Ctor_InvalidRectRegion_ThrowExcept()
{
	
	SU_ASSERT_THROW(RectRegion(Point(2, 5), Point(2, 6)), EasyExcept);
	SU_ASSERT_THROW(RectRegion(Point(2, 5), Point(3, 5)), EasyExcept);
	SU_ASSERT_THROW(RectRegion(Point(3, 5), Point(3, 5)), EasyExcept);
	SU_ASSERT_THROW(RectRegion(Point(4, 5), Point(1, 2)), EasyExcept);
}

////////////////////////////////////////////////////////////////////////////
//							Tests for PointArray

void PointArray_GetPoint_InvalidIndex_ThrowExcept()
{
	PointArray points{Point(0, 0)};

	SU_ASSERT_THROW(points.getPoint(2), EasyExcept);
}

void PointArray_InsertPoint_InvalidIndex_ThrowExcept()
{
	PointArray points{ Point(0, 0) };

	SU_ASSERT_THROW(points.insertPoint(2, Point(0, 0)), EasyExcept);
}

/////////////////////////////////////////////////////////////////////////////
//							Tests for Geometry

void Geometry_SetDotColor_ByDefault_DrawDotWithThisColor()
{
	Rgb color = Rgb(23, 45, 89);
	Window window;
	window.setAsDefault();

	Point point(23, 23);
	Geometry::setDotColor(color);
	Geometry::drawDot(point);

	assert(Geometry::getPointColor(point) == color.toColorref());
}

void Geometry_SetLineColor_ByDefault_DrawLineWithThisColor()
{
	Rgb color = Rgb(23, 34, 23);
	Window window;
	window.setAsDefault();

	Geometry::setLineColor(color);
	Geometry::drawLine(Point(0, 0), Point(40, 40));

	assert(Geometry::getPointColor(Point(20, 20)) == color.toColorref());
}

void Geometry_SetLineColor_SameColor_ColorNotChange()
{
	Window window;
	window.setAsDefault();
	const Colorable& oldColorValue = Geometry::getLineColor();

	Geometry::setLineColor(Geometry::getLineColor());

	assert(Geometry::getLineColor().toColorref() == oldColorValue.toColorref());
}

void Geometry_SetFillColor_ByDefault_DrawShapesWithThisColor()
{
	Rgb color = Rgb(11, 22, 33);
	Window window;
	window.setAsDefault();

	Geometry::setFillColor(color);
	Geometry::drawRectangle(RectRegion(Point(0, 0), Point(60, 60)));

	assert(Geometry::getPointColor(Point(30, 30)) == color.toColorref());
}

void Geometry_SetFillColor_SameColor_ColorNotChange()
{
	Window window;
	window.setAsDefault();
	const Colorable& oldColorValue = Geometry::getFillColor();

	Geometry::setFillColor(Geometry::getFillColor());

	assert(Geometry::getFillColor().toColorref() == oldColorValue.toColorref());
}

void Geometry_SetColors_DifferentWindow_KeepFormerColorSettings()
{
	Window firstWindow, secondWindow;
	Rgb firstDotColor(0, 1, 2), firstLineColor(3, 4, 5), firstFillColor(6, 7, 8);
	Rgb secondDotColor(1, 1, 1), secondLineColor(3, 3, 3), secondFillColor(6, 6, 6);

	firstWindow.setAsDefault();
	Geometry::setDotColor(firstDotColor);
	Geometry::setLineColor(firstLineColor);
	Geometry::setFillColor(firstFillColor);

	secondWindow.setAsDefault();
	Geometry::setDotColor(secondDotColor);
	Geometry::setLineColor(secondLineColor);
	Geometry::setFillColor(secondFillColor);

	firstWindow.setAsDefault();
	Geometry::drawDot(Point(1, 1));
	Geometry::drawLine(Point(2, 2), Point(4, 4));
	Geometry::drawRectangle(RectRegion(Point(5, 5), Point(8, 8)));
	assert( Geometry::getPointColor(Point(1, 1)) == firstDotColor.toColorref() );
	assert( Geometry::getPointColor(Point(3, 3)) == firstLineColor.toColorref() );
	assert(Geometry::getPointColor(Point(6, 6)) == firstFillColor.toColorref() );

	secondWindow.setAsDefault();
	Geometry::drawDot(Point(1, 1));
	Geometry::drawLine(Point(2, 2), Point(4, 4));
	Geometry::drawRectangle(RectRegion(Point(5, 5), Point(8, 8)));
	assert(Geometry::getPointColor(Point(1, 1)) == secondDotColor.toColorref());
	assert(Geometry::getPointColor(Point(3, 3)) == secondLineColor.toColorref());
	assert(Geometry::getPointColor(Point(6, 6)) == secondFillColor.toColorref());
}

void Geometry_DrawDot_ByDefault_DrawDotWithDotColor()
{
	Window window;
	window.setAsDefault();
	Point dot(23, 23);
	Rgb dotColor = Rgb::Coral();
	Geometry::setDotColor(dotColor);

	Geometry::drawDot(dot);

	assert(Geometry::getPointColor(dot) == dotColor.toColorref());
}

void Geometry_DrawLine_AfterDraw_DotColorAndLineColorNotChange()
{
	Window window;
	window.setAsDefault();

	Geometry::setDotColor(Rgb::Black());
	Geometry::setLineColor(Rgb::Blue());
	Geometry::setFillColor(Rgb::Coral());

	Geometry::drawLine(Point(1, 1), Point(2, 2));

	assert(Geometry::getDotColor().toColorref() != Geometry::getLineColor().toColorref());
}

void Geometry_DrawLine_ByDefault_IncludeTwoEndPoint()
{
	Window window;
	window.setAsDefault();
	Point from(0, 0), to(30, 20), middle(15, 10);
	Rgb lineColor(12, 22, 43);
	Geometry::setLineColor(lineColor);

	Geometry::drawLine(from, to);

	assert(Geometry::getPointColor(from) == lineColor.toColorref());
	assert(Geometry::getPointColor(middle) == lineColor.toColorref());
	assert(Geometry::getPointColor(to) == lineColor.toColorref());
}

void Geometry_DrawLine_TwoSameEnd_DrawOnePoint()
{
	Window window;
	window.setAsDefault();
	Point from(0, 0), to = from;
	Rgb lineColor(12, 22, 43);
	Geometry::setLineColor(lineColor);

	Geometry::drawLine(from, to);

	assert(Geometry::getPointColor(from) == lineColor.toColorref());
}

void Geometry_DrawArc_TwoPointsOneCenterOneNot_ThrowExcep()
{
	Window window;
	window.setAsDefault();

	SU_ASSERT_THROW(
		Geometry::drawArc(RectRegion(Point(0, 0), Point(40, 40)), Point(20, 20), Point(23, 45)),
		EasyExcept);
}

void Geometry_DrawArc_SameStartAndEndPoint_DrawEntireEllipse()
{
	Window window;
	window.setAsDefault();
	Rgb lineColor = Rgb::Blue();
	Geometry::setLineColor(lineColor);

	RectRegion bound(Point(0, 0), Point(40, 40));
	Geometry::drawArc(bound, Point(0, 0), Point(0, 0));

	assert(Geometry::getPointColor(Point(20, 0)) == lineColor.toColorref());
	assert(Geometry::getPointColor(Point(0, 20)) == lineColor.toColorref());
}

void Geometry_DrawBezier_PointNumberNotThreeTimePlusOne_ThrowExcept()
{
	Window window;
	window.setAsDefault();
	Rgb lineColor = Rgb::Blue();
	Geometry::setLineColor(lineColor);

	SU_ASSERT_THROW(
		Geometry::drawBeziers(PointArray{Point(0, 0)}),
		EasyExcept);
	SU_ASSERT_THROW(
		Geometry::drawBeziers(PointArray{ Point(0, 0), Point(1, 2) }),
		EasyExcept);
	SU_ASSERT_THROW(
		Geometry::drawBeziers(PointArray{ Point(0, 0), Point(1, 2), Point(0, 4) }),
		EasyExcept);
}

void Geometry_DrawBezier_ByDefault_IncludeTwoEndAndTwoControlPoints()
{
	Window window;
	window.setAsDefault();
	Rgb lineColor = Rgb::Blue();
	Geometry::setLineColor(lineColor);
	PointArray points{ Point(0, 0), Point(10, 10), Point(20, 20), Point(30, 30) };

	Geometry::drawBeziers(points);

	assert(
		Geometry::getPointColor(points.getPoint(0))
			==
		lineColor.toColorref());
	assert(
		Geometry::getPointColor(points.getPoint(1))
		==
		lineColor.toColorref());
	assert(
		Geometry::getPointColor(points.getPoint(2))
		==
		lineColor.toColorref());
	assert(
		Geometry::getPointColor(points.getPoint(3))
		==
		lineColor.toColorref());
}

void Geometry_DrawPolyline_PointNumberNotGreaterOne_ThrowExcept()
{
	Window window;
	window.setAsDefault();

	SU_ASSERT_THROW(
		Geometry::drawPolyline(PointArray{}),
		EasyExcept);
	SU_ASSERT_THROW(
		Geometry::drawPolyline(PointArray{Point(0, 0)}),
		EasyExcept);
}

void Geometry_DrawPolyline_ByDefault_IncludeAllStartAndEndsPoints()
{
	Window window;
	window.setAsDefault();
	Rgb lineColor = Rgb::Blue();
	Geometry::setLineColor(lineColor);
	PointArray points{ Point(0, 0), Point(10, 10), Point(20, 20)};

	Geometry::drawPolyline(points);

	assert(
		Geometry::getPointColor(points.getPoint(0))
		==
		lineColor.toColorref());
	assert(
		Geometry::getPointColor(points.getPoint(1))
		==
		lineColor.toColorref());
	assert(
		Geometry::getPointColor(points.getPoint(2))
		==
		lineColor.toColorref());
}

void Geometry_DrawChord_EndPointsOneCenterAnotherNot_ThrowExcept()
{
	Window window;
	window.setAsDefault();

	SU_ASSERT_THROW(
		Geometry::drawChord(RectRegion(Point(0, 0), Point(10, 10)), Point(5, 5), Point(1, 2)),
		EasyExcept);
}

void Geometry_DrawRectangle_ByDegault_IncludeBottomLineAndRightLine()
{
	Window window;
	window.setAsDefault();
	Rgb lineColor = Rgb::Blue();
	Geometry::setLineColor(lineColor);

	Geometry::drawRectangle(RectRegion(Point(0, 0), Point(10, 10)));

	assert(
		Geometry::getPointColor(Point(0, 0)) == lineColor.toColorref());
	assert(
		Geometry::getPointColor(Point(0, 10)) == lineColor.toColorref());
	assert(
		Geometry::getPointColor(Point(10, 0)) == lineColor.toColorref());
	assert(
		Geometry::getPointColor(Point(10, 10)) == lineColor.toColorref());
}

void Geometry_DrawPie_TwoEndsOneCanterOneAnoter_ThrowExcept()
{
	Window window;
	window.setAsDefault();

	SU_ASSERT_THROW(
		Geometry::drawPie(RectRegion(Point(0, 0), Point(10, 10)), Point(5, 5), Point(1, 2)),
		EasyExcept);
}

void Geometry_DrawPolygon_PointNumberLessThree_ThrowExcept()
{
	Window window;
	window.setAsDefault();

	SU_ASSERT_THROW(
		Geometry::drawPolygon(PointArray{ Point(0, 0) }),
		EasyExcept);
	SU_ASSERT_THROW(
		Geometry::drawPolygon(PointArray{ Point(0, 0), Point(23, 34) }),
		EasyExcept);
}

//#error "test color module, change attribute name"