#ifndef DVector3_H
#define DVector3_H

class Vector3
{
public:
	double x,y,z;

	Vector3():x(0),y(0),z(0){};
	Vector3(double myX,double myY,double myZ)
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