#pragma once
#include <iostream>
using namespace std;
class Point
{
private:
	int x;
	int y;
public:
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(int scalar) : x(scalar), y(scalar)
	{

	}
	Point(int a, int b) : x(a), y(b)
	{

	}
	Point(const Point& other) : x(other.x), y(other.y)
	{
		//cout << "Copy" << endl;
	}
	Point(Point&& other) : x(other.x), y(other.y)
	{
		//cout << "Move" << endl;
	}
	Point& operator=(const Point& other) 
	{
		//cout << "Copy" << endl;
		x = other.x;
		y = other.y;
		return *this;
	}
	Point& operator=(Point&& other)
	{
		//cout << "Move" << endl;
		x = other.x;
		y = other.y;
		return *this;

	}
	~Point()
	{
		//cout << "Delete\n";
	}
	friend std::ostream& operator << (std::ostream& out, const Point& point)
	{
		out << "X:" << point.x << " Y:" << point.y;
		return out;
	}
};