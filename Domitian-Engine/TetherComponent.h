#ifndef DTetherComp_H
#define DTetherComp_H

#include "Component.h"
#include "PhysicsComp.h"
#include "PositionComp.h"

class TetherComp : public Component
{
public:
	TetherComp(float myTetherLength,
			   PositionComp* myFirst,	float myFirstRadius,		  float myFirstRadianToTether,
			   PositionComp* mySecond,	float mySecondRadianToTether, float mySecondRadius);

	void update(double);

private:
	float tether_length;

	PositionComp* first_position_comp; 
	PhysicsComp* first_physics_comp;
	Vector2 first_tether_position;
	float first_radius;
	float first_radian_to_tether;

	PositionComp* second_position_comp;
	PhysicsComp* second_physics_comp;
	Vector2 second_tether_position;
	float second_radius;
	float second_radian_to_tether;
};
#endif