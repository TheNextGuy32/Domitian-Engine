#include "Force.h"

Force::Force(Vector2 myDisplacement,float myDirection, float myForce)
{
	displacement = myDisplacement;
	radian_direction = myDirection;
	force = myForce;
}
Force::Force(float myDirection, float myForce)
{
	radian_direction = myDirection;
	force = myForce;
}
