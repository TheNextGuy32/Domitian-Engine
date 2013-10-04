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
		if(first.x==second.x)
		{
			if(first.y==second.y)
			{
				return true;
			}
		}
		return false;
	}

};