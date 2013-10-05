#ifndef DVector3_H
#define DVector3_H

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
		return(first.x==second.x && first.y==second.y && first.z==second.z);
	}

};
#endif