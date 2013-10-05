#ifndef DVector2_H
#define DVector2_H

class Vector2
{
public:
	float x,y;
	Vector2(float myX,float myY)
	{
		x = myX;
		y = myY;
	}
	static bool Equals(Vector2 first, Vector2 second)
	{
		return (first.x==second.x && first.y==second.y);
	}

};
#endif