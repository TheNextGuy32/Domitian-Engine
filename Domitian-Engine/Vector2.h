#ifndef DVector2_H
#define DVector2_H

#include <cmath>

class Vector2
{
public:
	double x,y;
	Vector2():x(0),y(0){};
	Vector2(double myX,double myY)
	{
		x = myX;
		y = myY;
	}

	bool Equals(Vector2 first, Vector2 second)
	{
		return (first.x==second.x && first.y==second.y);
	}
	static double ToMathRadian(Vector2 myVector)
	{
		return atan2(myVector.y,myVector.x);
	};
	static Vector2 ToVector2(double angle)
	{
		return Vector2 (cos(angle), sin(angle));
	};

	Vector2 &operator+=(Vector2 other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2 operator+(Vector2 other)
	{
		Vector2 ret(*this);
		ret += other;
		return ret;
	}
	Vector2 &operator-=(Vector2 other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2 operator-(Vector2 other)
	{
		Vector2 ret(*this);
		ret -= other;
		return ret;
	}

	static double getDistanceBetween(Vector2 first, Vector2 second)
	{
		return sqrt( (second.x-first.x)*(second.x-first.x) + (second.y-first.y)*(second.y-first.y));
	}
};
#endif