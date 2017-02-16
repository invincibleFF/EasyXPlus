#include "easyGeometry.h"
#include "easyWindow.h"
#include "easyExcept.h"

#include <cassert>

using namespace easyXPlus;

namespace easyXPlus
{
	////////////////////////////////////////////////////////////////////////////////
	//									Point

	bool Point::operator == (const Point& another)const
	{
		return	this->getX() == another.getX() &&
				this->getY() == another.getY();
	}
	
	bool Point::operator != (const Point& another)const
	{
		return !((*this) == another);
	}

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

	////////////////////////////////////

	Point RectRegion::getCenter()const
	{
		return Point(
			(leftTop.getX() + rightBottom.getX()) / 2,
			(leftTop.getY() + rightBottom.getY())  / 2);
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

	std::vector<HPEN>	Geometry::penHandles;
	std::vector<HBRUSH>	Geometry::brushHandles;

	/////////////////////////////////

	COLORREF Geometry::getDotColor()
	{
		//	test if setAsDefault() called
		Window::getDefaultAttribute();

		return dotColor;
	}

	/////////////////////////////////

	COLORREF Geometry::getLineColor()
	{
		return Window::getDefaultAttribute()->lineColor;
	}

	/////////////////////////////////

	COLORREF Geometry::getFillColor()
	{
		return Window::getDefaultAttribute()->fillColor;
	}

	/////////////////////////////////

	void Geometry::setDotColor(const Colorable& color)
	{
		dotColor = color.toColorref();
	}

	/////////////////////////////////

	void Geometry::setLineColor(const Colorable& color)
	{
		HPEN penHandle = CreatePen(PS_SOLID, 0, color.toColorref());
		if (NULL == penHandle)
			throw EasyExcept("System call error!");
		else
			penHandles.push_back(penHandle);

		HGDIOBJ objRet = SelectObject(
			Window::getDefaultAttribute()->hdc, (HGDIOBJ)penHandle);

		if (NULL == objRet)
			throw EasyExcept("System call error!");

		Window::getDefaultAttribute()->lineColor = color.toColorref();
	}

	/////////////////////////////////////

	void Geometry::setFillColor(const Colorable& color)
	{
		HBRUSH brushHandle = CreateSolidBrush(color.toColorref());
		if (NULL == brushHandle)
			throw EasyExcept("System call error!");
		else
			brushHandles.push_back(brushHandle);

		HGDIOBJ objRet = SelectObject(
			Window::getDefaultAttribute()->hdc, (HGDIOBJ)brushHandle);

		if (NULL == objRet)
			throw EasyExcept("System call error!");

		Window::getDefaultAttribute()->fillColor = color.toColorref();
	}

	///////////////////////////////////////

	COLORREF Geometry::getPointColor(Point point)
	{
		COLORREF retColor = GetPixel(
			Window::getDefaultAttribute()->hdc, point.getX(), point.getY());

		if (retColor == CLR_INVALID)
			throw EasyExcept("System call error!");
		else
			return retColor;
	}

	///////////////////////////////////////

	void Geometry::drawDot(Point point)
	{
		COLORREF colorRet = SetPixel(
			Window::getDefaultAttribute()->hdc, point.getX(), point.getY(), dotColor);

		if (colorRet == -1 || colorRet == ERROR_INVALID_PARAMETER)
			throw EasyExcept("System call error!");
	}

	///////////////////////////////////////

	void Geometry::drawLine(Point from, Point to)
	{
		HDC hdc = Window::getDefaultAttribute()->hdc;

		if (0 == MoveToEx(hdc, from.getX(), from.getY(), NULL))
			throw EasyExcept("System call error!");

		if (0 == LineTo(hdc, to.getX(), to.getY()))
			throw EasyExcept("System call error!");

		//	in GDI, the last pixel is not drew
		COLORREF oldDotColor = Geometry::getDotColor();
		Geometry::setDotColor(Rgb::White().fromColorref(Geometry::getLineColor()));
		Geometry::drawDot(to);
		Geometry::setDotColor(Rgb::White().fromColorref(oldDotColor));
	}

	///////////////////////////////////////

	void Geometry::drawArc(RectRegion bound, Point start, Point end)
	{
		checkTwoEndPoints(bound, start, end);

		BOOL ret = Arc(
			Window::getDefaultAttribute()->hdc,
			bound.getLeftTop().getX(),
			bound.getLeftTop().getY(),
			bound.getRightBottom().getX(),
			bound.getRightBottom().getY(),
			start.getX(),
			start.getY(),
			end.getX(),
			end.getY());
		if (ret == 0)	throw EasyExcept("System call error!");

		//	Since the intersect point is hard to calculate and points in mathematics
		//	cannot be strictly represented in displays, i choose to let the two-end
		//	points go.
	}

	void Geometry::checkTwoEndPoints(const RectRegion& bound, const Point& start, const Point& end)
	{
		Point centerPoint = bound.getCenter();

		//	one point is center, another not, invalid!!
		if ( start != end &&
			(centerPoint == start || centerPoint == end))

			throw EasyExcept("Two points invalid!");
	}

	///////////////////////////////////////

	void Geometry::drawBeziers(PointArray points)
	{
		//	bezier curves need (3n + 1) point to draw itself
		if ( (points.getSize() % 3) != 1 )
			throw EasyExcept("The number of points is invalid!");

		
		POINT* pointArray = convertToPOINTs(points);
		BOOL ret = PolyBezier(
			Window::getDefaultAttribute()->hdc, pointArray, points.getSize());

		delete[] pointArray;
		if (ret == 0)	throw EasyExcept("System call error");

		//	in GDI, the end point is not drew. Use drawLine() bacause drawDot()
		//	uses different drawing color
		const Point& lastPoint = points.getPoint(points.getSize() - 1);
		Geometry::drawLine(lastPoint, lastPoint);
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
			Window::getDefaultAttribute()->hdc, pointArray, points.getSize());

		delete[] pointArray;
		if (ret == 0)	throw EasyExcept("System call error!");

		//	in GDI, the last point is not drew. Use drawLine() bacause drawDot()
		//	uses different drawing color
		const Point& lastPoint = points.getPoint(points.getSize() - 1);
		Geometry::drawLine(lastPoint, lastPoint);
	}

	/////////////////////////////////////////

	void Geometry::drawChord(RectRegion bound, Point start, Point end)
	{
		checkTwoEndPoints(bound, start, end);

		BOOL ret = Chord(
			Window::getDefaultAttribute()->hdc,
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
			Window::getDefaultAttribute()->hdc,
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
			Window::getDefaultAttribute()->hdc,
			rectRegion.getLeftTop().getX(),
			rectRegion.getLeftTop().getY(),
			rectRegion.getRightBottom().getX(),
			rectRegion.getRightBottom().getY());
		if (ret == 0)	throw EasyExcept("System call error!");

		Geometry::drawLine(
			Point(rectRegion.getLeftTop().getX(), rectRegion.getRightBottom().getY()),
			Point(rectRegion.getRightBottom()));
		Geometry::drawLine(
			Point(rectRegion.getRightBottom().getX(), rectRegion.getLeftTop().getY()),
			Point(rectRegion.getRightBottom()));
	}

	///////////////////////////////////////////

	void Geometry::drawRoundRectangle(RectRegion rectRegion, Rectangle rectangle)
	{
		unsigned regionWidth = 
			rectRegion.getRightBottom().getX() - rectRegion.getLeftTop().getX();
		unsigned regionHeight =
			rectRegion.getRightBottom().getY() - rectRegion.getLeftTop().getY();

		if (rectangle.getWidth() > regionWidth ||
			rectangle.getHeight() > regionHeight)

			throw EasyExcept("Rectangle invalid!");

		BOOL ret = RoundRect(
			Window::getDefaultAttribute()->hdc,
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
		checkTwoEndPoints(bound, start, end);

		BOOL ret = Pie(
			Window::getDefaultAttribute()->hdc,
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
		if (points.getSize() < 3)
			throw EasyExcept("System call error!");

		POINT* pointArray = convertToPOINTs(points);
		BOOL ret = Polygon(
			Window::getDefaultAttribute()->hdc, pointArray, points.getSize());

		delete[] pointArray;
		if (ret == 0)	throw EasyExcept("System call error!");
	}

}