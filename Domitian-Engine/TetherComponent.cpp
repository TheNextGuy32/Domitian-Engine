#include "TetherComponent.h"

TetherComp::TetherComp(float myTetherLength,
				PositionComp* myFirstPos,	PhysicsComp* myFirstPhys,	float myFirstRadius,  float myFirstRadianToTether,
			    PositionComp* mySecondPos,	PhysicsComp* mySecondPhys,	float mySecondRadius, float mySecondRadianToTether)
	: Component("Tether")
{
	tether_length = myTetherLength;
	first_position_comp = myFirstPos;
	first_physics_comp = myFirstPhys;
	first_radius = myFirstRadius;
	first_radian_to_tether = myFirstRadianToTether;

	second_position_comp = mySecondPos;
	second_physics_comp = mySecondPhys;
	second_radius = mySecondRadius;
	second_radian_to_tether = mySecondRadianToTether;

	first_tether_position =Vector2(0,0);
	second_tether_position = Vector2(0,0);
};

void TetherComp::update(double dt)
{
	first_tether_position = Vector2(first_position_comp->getPosition().x + (cos(first_radian_to_tether+first_position_comp->getRotation())*first_radius),
		first_position_comp->getPosition().y + (sin(first_radian_to_tether+first_position_comp->getRotation())*first_radius));

	second_tether_position = Vector2(second_position_comp->getPosition().x + (cos(second_radian_to_tether+second_position_comp->getRotation())*second_radius),
		second_position_comp->getPosition().y + (sin(second_radian_to_tether+second_position_comp->getRotation())*second_radius));

	if(Vector2::getDistanceBetween(first_tether_position,second_tether_position) > tether_length)
	{
		//We are at the extent of the thing
		Vector2 displacement_to_second_tether_from_first_tether = Vector2((second_tether_position.x - first_tether_position.x),-(second_tether_position.y - first_tether_position.y));
		Vector2 displacement_to_first_tether_from_second_tether = Vector2((first_tether_position.x - second_tether_position.x),-(first_tether_position.y - second_tether_position.y));
		
		double both_mass = first_physics_comp->getMass() + second_physics_comp->getMass();

		Vector2 first_velocity = first_physics_comp->getVelocity();
		Vector2 first_normalized_velocity= Vector2::Normalize(first_velocity);

		Vector2 second_velocity = second_physics_comp->getVelocity();
		Vector2 second_normalized_velocity = Vector2::Normalize(second_velocity);

		//In this solution, we are going to only apply the momentum in the direction of the tether
		//sin angle made between

		displacement_to_first_tether_from_second_tether.Normalize();
		displacement_to_second_tether_from_first_tether.Normalize();

		double tension_force_applied_to_second = (first_velocity.x *displacement_to_first_tether_from_second_tether.x)+(first_velocity.y *displacement_to_first_tether_from_second_tether.y) * first_physics_comp->getMass();
		double tension_force_applied_to_first = (second_velocity.x *displacement_to_second_tether_from_first_tether.x)+(second_velocity.y *displacement_to_second_tether_from_first_tether.y) * second_physics_comp->getMass();
			

		//This is my centripedal solution, doesnt seem to make sense
		////Wait, are we still using the smallest angle
		//Vector2 normal_of_tether = Vector2(-displacement_to_second_tether_from_first_tether.x,displacement_to_second_tether_from_first_tether.y);
		//normal_of_tether.Normalize();

		//double dot_product_of_tether_normal_and_first_velocity=acos((first_normalized_velocity.x * normal_of_tether.x)+(first_normalized_velocity.y * normal_of_tether.y));
		//double first_radian_between_normal_and_velocity = cos(dot_product_of_tether_normal_and_first_velocity);//We can assume this are unit vecotrs anchored at origin
		//double first_centripedal_velocity = first_radian_between_normal_and_velocity * first_velocity.GetLength();

		//double dot_product_of_tether_normal_and_second_velocity=acos((second_normalized_velocity.x * normal_of_tether.x)+(second_normalized_velocity.y * normal_of_tether.y));
		//double second_radian_between_normal_and_velocity = cos(dot_product_of_tether_normal_and_second_velocity);//We can assume this are unit vecotrs anchored at origin
		//double second_centripedal_velocity = second_radian_between_normal_and_velocity * second_velocity.GetLength();

		//double tension_force_applied_to_second = (first_centripedal_velocity* first_centripedal_velocity)/tether_length* first_physics_comp->getMass();
		//double tension_force_applied_to_first = (second_centripedal_velocity*second_centripedal_velocity)/tether_length* second_physics_comp->getMass();
		
		double radian_to_first_tether_angled = first_radian_to_tether+first_position_comp->getRotation();
		double radian_to_second_tether = Vector2::ToMathRadian(displacement_to_first_tether_from_second_tether);
		double direction_tether_pull_angled = radian_to_second_tether+first_position_comp->getRotation();

		//It has to be negative because positive is a push, neg is a pull
		first_physics_comp->addForceWithRadius(Force(radian_to_first_tether_angled,direction_tether_pull_angled,-tension_force_applied_to_first),first_radius);
		second_physics_comp->addForceWithRadius(Force(second_radian_to_tether+second_position_comp->getRotation(),Vector2::ToMathRadian(displacement_to_first_tether_from_second_tether)+second_position_comp->getRotation(),-tension_force_applied_to_second),second_radius);
	}
};