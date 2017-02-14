#ifndef EASY_GEOMETRY_H
#define EASY_GEOMETRY_H

#include "easyColor.h"
#include <vector>

namespace easyXPlus
{
	//	A point in a coordinate system.
	class Point
	{
	public:
		Point(unsigned X, unsigned Y) : x(X), y(Y)
		{}

		unsigned getX() const	{ return x; }
		unsigned getY() const	{ return y; }

	private:
		unsigned x, y;
	};

	//	A Rect-Region is a rectangular area in the coordinate system. It is denoted by
	//	a left-top point and a right-bottom point.
	class RectRegion
	{
	public:
		RectRegion(Point leftTopPoint, Point rightBottomPoint);

		Point getLeftTop() const	{ return leftTop; }
		Point getRightBottom() const	{ return rightBottom; }

	private:
		Point leftTop, rightBottom;
	};

	//	A rectangle is an "RectRegion" without coordinate information. Thus, it is only
	//	limited by width and height.
	class Rectangle
	{
	public:
		Rectangle(unsigned width, unsigned height) : width(width), height(height)
		{}

		unsigned getWidth() const	{ return width; }
		unsigned getHeight() const	{ return height; }

	private:
		unsigned width, height;
	};

	class PointArray
	{
	public:
		PointArray(std::initializer_list<Point> points);

		bool isEmpty() const;
		unsigned getSize() const;
		Point getPoint(unsigned index) const;
		void appendPoint(Point point);
		void erasePoint(unsigned index);
		void assignPoint(unsigned index, Point point);
		void insertPoint(unsigned indexBefore, Point point);
		void clearAll();

	private:
		std::vector<Point>	points;
	};

	//	TODO:
	//		To make setDotColor() only applys to the window set, not always the
	//		current window.
	class Geometry
	{
	public:
		static void setDotColor(const Colorable& color);
		static void setLineColor(const Colorable& color);
		static void setFillColor(const Colorable& color);

		static COLORREF getPointColor(Point point);

		//	Dot

		static void drawDot(Point point);

		//	Lines

		static void drawLine(Point from, Point to);
		static void drawArc(RectRegion bound, Point start, Point end);
		static void drawBeziers(PointArray points);
		static void drawPolyline(PointArray points);

		//	Filled shapes

		static void drawChord(RectRegion bound, Point start, Point end);
		static void drawEllipse(RectRegion bound);
		static void drawRectangle(RectRegion rectRegion);
		static void drawRoundRectangle(RectRegion rectRegion, Rectangle ellipseBound);
		static void drawPie(RectRegion bound, Point start, Point end);
		static void drawPolygon(PointArray points);

	private:
		static POINT* convertToPOINTs(const PointArray& points);

		static COLORREF dotColor;

		//	handles need to be deleted
		static std::vector<HPEN>	penHandles;
		static std::vector<HBRUSH>	brushHandles;
	};
}

#endif