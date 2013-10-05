#ifndef DVector2_H
#define DVector2_H

class Vector2
{
public:
	float x,y;
	Vector2():x(0),y(0){};
	Vector2(float myX,float myY)
	{
		x = myX;
		y = myY;
	}
	static bool Equals(Vector2 first, Vector2 second)
	{
		return (first.x==second.x && first.y==second.y);
	}
	
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
};
#endif