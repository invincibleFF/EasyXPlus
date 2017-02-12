#include "easyGeometry.h"
#include "easyWindow.h"
#include "easyExcept.h"

#include <cassert>

using namespace easyXPlus;

namespace easyXPlus
{
	////////////////////////////////////////////////////////////////////////////////
	//									RectRegion

	RectRegion::RectRegion(Point leftTopPoint, Point rightBottomPoint)
		: leftTop(leftTopPoint), rightBottom(rightBottomPoint)
	{
		//	invalid rectangular-region
		if (leftTop.getX() >= rightBottom.getX() ||
			leftTop.getY() >= rightBottom.getY())

			throw EasyExcept("Invalid RectRegion!");
	}

	////////////////////////////////////////////////////////////////////////////////
	//									PointArray

	PointArray::PointArray(std::initializer_list<Point> points)
		: points(points)
	{}

	///////////////////////////////////

	inline bool PointArray::isEmpty() const
	{
		return points.empty();
	}

	///////////////////////////////////

	inline unsigned PointArray::getSize() const
	{
		return points.size();
	}

	///////////////////////////////////

	Point PointArray::getPoint(unsigned index) const
	{
		try
		{
			return points.at(index);
		}
		catch (std::out_of_range exception)
		{
			throw EasyExcept("Index error!");
		}
	}

	///////////////////////////////////

	void PointArray::appendPoint(Point point)
	{
		points.push_back(point);
	}

	//////////////////////////////////

	void PointArray::insertPoint(unsigned indexBefore, Point point)
	{
		if (indexBefore > points.size())
			throw EasyExcept("Index error");

		points.insert(points.begin() + indexBefore, point);
	}

	//////////////////////////////////

	void PointArray::assignPoint(unsigned index, Point point)
	{
		points.at(index) = point;
	}

	//////////////////////////////////

	void PointArray::erasePoint(unsigned index)
	{
		points.erase(points.begin() + index);
	}

	//////////////////////////////////

	void PointArray::clearAll()
	{
		points.clear();
	}

	///////////////////////////////////////////////////////////////////////////
	//								Geometry

	//	static variables

	COLORREF Geometry::dotColor = Rgb::White().toColorref();
	COLORREF Geometry::lineColor = Rgb::Black().toColorref();
	COLORREF Geometry::fillColor = Rgb::White().toColorref();

	std::vector<HPEN>	Geometry::penHandles;
	std::vector<HBRUSH>	Geometry::brushHandles;

	/////////////////////////////////

	void Geometry::setDotColor(const Colorable& color)
	{
		dotColor = color.toColorref();
	}

	/////////////////////////////////

	void Geometry::setLineColor(const Colorable& color)	{
		lineColor = color.toColorref();

		HPEN penHandle = CreatePen(PS_SOLID, 0, lineColor);
		if (NULL == penHandle)
			throw EasyExcept("System call error!");
		else
			penHandles.push_back(penHandle);

		HGDIOBJ objRet = SelectObject(
			Window::getDefaultDC(), (HGDIOBJ)penHandle);

		if (NULL == objRet)
			throw EasyExcept("System call error!");
	}

	/////////////////////////////////////

	void Geometry::setFillColor(const Colorable& color)
	{
		fillColor = color.toColorref();

		HBRUSH brushHandle = CreateSolidBrush(fillColor);
		if (NULL == brushHandle)
			throw EasyExcept("System call error!");
		else
			brushHandles.push_back(brushHandle);

		HGDIOBJ objRet = SelectObject(
			Window::getDefaultDC(), (HGDIOBJ)brushHandle);

		if (NULL == objRet)
			throw EasyExcept("System call error!");
	}

	//////////////////////////////////////

	COLORREF Geometry::getLineColor()
	{
		return lineColor;
	}

	///////////////////////////////////////

	COLORREF Geometry::getFillColor()
	{
		return fillColor;
	}

	///////////////////////////////////////

	COLORREF Geometry::getDotColor()
	{
		return dotColor;
	}

	///////////////////////////////////////

	COLORREF Geometry::getPointColor(Point point)
	{
		COLORREF retColor = GetPixel(
			Window::getDefaultDC(), point.getX(), point.getY());

		if (retColor == CLR_INVALID)
			throw EasyExcept("System call error!");
		else
			return retColor;
	}

	///////////////////////////////////////

	void Geometry::drawDot(Point point)
	{
		COLORREF colorRet = SetPixel(
			Window::getDefaultDC(), point.getX(), point.getY(), dotColor);

		if (colorRet == -1 || colorRet == ERROR_INVALID_PARAMETER)
			throw EasyExcept("System call error!");
	}

	///////////////////////////////////////

	void Geometry::drawLine(Point from, Point to)
	{
		HDC hdc = Window::getDefaultDC();

		if (0 == MoveToEx(hdc, from.getX(), from.getY(), NULL))
			throw EasyExcept("System call error!");

		//	in GDI, the last pixel is not drew
		if (0 == LineTo(hdc, to.getX() + 1, to.getY() + 1))
			throw EasyExcept("System call error!");
	}

	///////////////////////////////////////

	void Geometry::drawArc(RectRegion bound, Point start, Point end)
	{
		BOOL ret = Arc(
			Window::getDefaultDC(),
			bound.getLeftTop().getX(),
			bound.getLeftTop().getY(),
			bound.getRightBottom().getX(),
			bound.getRightBottom().getY(),
			start.getX(),
			start.getY(),
			end.getX(),
			end.getY());

		if (ret == 0)	throw EasyExcept("System call error!");
	}

	///////////////////////////////////////

	void Geometry::drawBeziers(PointArray points)
	{
		//	bezier curves need (3n + 1) point to draw itself
		if ( (points.getSize() % 3) != 1 )
			throw EasyExcept("The number of points is invalid!");

		
		POINT* pointArray = convertToPOINTs(points);
		BOOL ret = PolyBezier(
			Window::getDefaultDC(), pointArray, points.getSize());

		delete[] pointArray;
		if (ret == 0)	throw EasyExcept("System call error");
	}

	POINT* Geometry::convertToPOINTs(const PointArray& points)
	{
		POINT* pointArray = new POINT[points.getSize()];
		for (unsigned i = 0; i < points.getSize(); ++i)
			pointArray[i].x = points.getPoint(i).getX(),
			pointArray[i].y = points.getPoint(i).getY();

		return pointArray;
	}

	///////////////////////////////////////

	void Geometry::drawPolyline(PointArray points)
	{
		//	polyline -> point number greater equal than 2
		if (points.getSize() < 2)
			throw EasyExcept("System call error!");

		POINT* pointArray = convertToPOINTs(points);
		BOOL ret = Polyline(
			Window::getDefaultDC(), pointArray, points.getSize());

		delete[] pointArray;
		if (ret == 0)	throw EasyExcept("System call error!");
	}

	/////////////////////////////////////////

	void Geometry::drawChord(RectRegion bound, Point start, Point end)
	{
		BOOL ret = Chord(
			Window::getDefaultDC(),
			bound.getLeftTop().getX(),
			bound.getLeftTop().getY(),
			bound.getRightBottom().getX(),
			bound.getRightBottom().getY(),
			start.getX(),
			start.getY(),
			end.getX(),
			end.getY());

		if (ret == 0)	throw EasyExcept("System call error!");
	}

	////////////////////////////////////////

	void Geometry::drawEllipse(RectRegion bound)
	{
		BOOL ret = Ellipse(
			Window::getDefaultDC(),
			bound.getLeftTop().getX(),
			bound.getLeftTop().getY(),
			bound.getRightBottom().getX(),
			bound.getRightBottom().getY());

		if (ret == 0)	throw EasyExcept("System call error!");
	}

	//////////////////////////////////////////

	void Geometry::drawRectangle(RectRegion rectRegion)
	{
		BOOL ret = ::Rectangle(
			Window::getDefaultDC(),
			rectRegion.getLeftTop().getX(),
			rectRegion.getLeftTop().getY(),
			rectRegion.getRightBottom().getX(),
			rectRegion.getRightBottom().getY());

		if (ret == 0)	throw EasyExcept("System call error!");
	}

	///////////////////////////////////////////

	void Geometry::drawRoundRectangle(RectRegion rectRegion, Rectangle rectangle)
	{
		BOOL ret = RoundRect(
			Window::getDefaultDC(),
			rectRegion.getLeftTop().getX(),
			rectRegion.getLeftTop().getY(),
			rectRegion.getRightBottom().getX(),
			rectRegion.getRightBottom().getY(),
			rectangle.getWidth(),
			rectangle.getHeight());

		if (ret == 0)	throw EasyExcept("System call error!");
	}

	///////////////////////////////////////////

	void Geometry::drawPie(RectRegion bound, Point start, Point end)
	{
		BOOL ret = Pie(
			Window::getDefaultDC(),
			bound.getLeftTop().getX(),
			bound.getLeftTop().getY(),
			bound.getRightBottom().getY(),
			bound.getRightBottom().getY(),
			start.getX(),
			start.getY(),
			end.getX(),
			end.getY());

		if (ret == 0)	throw EasyExcept("System call error!");
	}

	/////////////////////////////////////////////

	void Geometry::drawPolygon(PointArray points)
	{
		if (points.getSize() < 2)
			throw EasyExcept("System call error!");

		POINT* pointArray = convertToPOINTs(points);
		BOOL ret = Polygon(
			Window::getDefaultDC(), pointArray, points.getSize());

		delete[] pointArray;
		if (ret == 0)	throw EasyExcept("System call error!");
	}

}