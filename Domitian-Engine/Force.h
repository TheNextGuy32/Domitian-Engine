#ifndef DForce
#define DForce

#include "Vector2.h"

class Force
{
public:
	Force(Vector2,float,float);
	Force(float, float);

	Vector2 getDisplacement()
	{
		return displacement;
	};

	float getRadianDirection()
	{
		return radian_direction;
	};

	float getForce()
	{
		return force;
	};

private:
	Vector2 displacement;
	float radian_direction;
	float force;

};
#endif