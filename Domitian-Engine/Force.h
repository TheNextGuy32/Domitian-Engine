#ifndef DForce
#define DForce

#include "Vector2.h"
#include "Radian.h"

class Force
{
public:
	Force(float,float,float);

	float getMathRadianToForce()
	{
		return direction_to_force;
	};

	float getForceMathRadian()
	{
		return force_direction;
	};

	float getForce()
	{
		return force;
	};

private:
	float direction_to_force;
	float force_direction;
	float force;

};
#endif