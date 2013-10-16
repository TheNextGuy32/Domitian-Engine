#include "Force.h"


Force::Force(float myDirectionToForce,float myForceDirection, float myForce) : force(myForce)
{
	direction_to_force = myDirectionToForce;
	force_direction = myForceDirection;
}