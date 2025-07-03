#include "Shape.h"

Shape::Shape(){}
Shape::~Shape(){}
double Shape::getarea() const
{
	return 0;
}


Circle::Circle(double radius): m_radius(radius) 
{
}
Circle::~Circle() 
{
}
double Circle::getarea() const
{
	return 3.1415926 * m_radius * m_radius;
}


Rectangle::Rectangle(double length, double width) : m_length(length), m_width(width)
{
}
Rectangle::~Rectangle()
{
}
double Rectangle::getarea() const
{
	return m_length * m_width;
}


Square::Square(double sideLength) : m_sideLength(sideLength)
{
}
Square::~Square()
{
}
double Square::getarea() const
{
	return m_sideLength * m_sideLength;
}