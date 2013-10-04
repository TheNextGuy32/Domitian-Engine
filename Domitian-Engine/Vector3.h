class Vector3
{
public:
	float x,y,z;
	Vector3(float myX,float myY,float myZ)
	{
		x = myX;
		y = myY;
		z = myZ;
	}
	static bool Equals(Vector3 first, Vector3 second)
	{
		if(first.x==second.x)
		{
			if(first.y==second.y)
			{
				if(first.z==second.z)
				{
					return true;
				}
			}
		}
		return false;
	}

};