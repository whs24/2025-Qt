#pragma once
class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual double getarea() const;
};

class Circle : public Shape
{
public:
	Circle(double radius);
	~Circle();
	double getarea() const;
private:
	double m_radius;
};

class Rectangle : public Shape
{
public:
	Rectangle(double length, double width);
	~Rectangle();
	double getarea() const;
private:
	double m_length;
	double m_width;
};

class Square : public Shape
{
public:
	Square(double sideLength);
	~Square();
	double getarea() const;
private:
	double m_sideLength;
};
