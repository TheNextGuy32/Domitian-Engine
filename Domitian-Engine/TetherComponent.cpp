#include "TetherComponent.h"

TetherComp::TetherComp(float myTetherLength,//Consider adding tether breaking
					   PositionComp* myFirst,float myFirstRadius,float myFirstRadianToTether, 
					   PositionComp* mySecond,float mySecondRadianToTether, float mySecondRadius)
	: Component("Tether")
{

	first_position_comp = myFirst;
	first_physics_comp = (PhysicsComp*)first_position_comp->getComponent("Physics");
	first_radius = myFirstRadius;
	first_radian_to_tether = myFirstRadianToTether;

	second_position_comp = mySecond;
	second_physics_comp = (PhysicsComp*)second_physics_comp->getComponent("Physics");
	second_radius = mySecondRadius;
	second_radian_to_tether = mySecondRadianToTether;

	first_tether_position =Vector2(0,0);
	second_tether_position = Vector2(0,0);
};

void TetherComp::update(double dt)
{
	first_tether_position = Vector2(first_position_comp->getPosition().x + (cos(first_radian_to_tether)*first_radius),
		first_position_comp->getPosition().y + (sin(first_radian_to_tether)*first_radius));

	second_tether_position = Vector2(second_position_comp->getPosition().x + (cos(second_radian_to_tether)*second_radius),
		second_position_comp->getPosition().y + (sin(second_radian_to_tether)*second_radius));

	if(Vector2::getDistanceBetween(first_tether_position,second_tether_position) > tether_length)
	{
		//We are at the extent of the thing
		Vector2 direction_to_second_tether_from_first_tether = Vector2(-(second_tether_position.x - first_tether_position.x),-(second_tether_position.y - first_tether_position.y));
		Vector2 direction_to_first_tether_from_second_tether = Vector2(-(first_tether_position.x - second_tether_position.x),-(first_tether_position.y - second_tether_position.y));
		
		double first_tension_force = 0;
		double second_tension_force = 0;

		first_physics_comp->addForceWithRadius(Force(first_radian_to_tether,Vector2::ToMathRadian(direction_to_second_tether_from_first_tether),first_tension_force),first_radius);
		second_physics_comp->addForceWithRadius(Force(second_radian_to_tether,Vector2::ToMathRadian(direction_to_first_tether_from_second_tether),second_tension_force),second_radius);
	}
};