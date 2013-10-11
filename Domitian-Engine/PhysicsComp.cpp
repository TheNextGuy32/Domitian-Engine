#include "PhysicsComp.h"


PhysicsComp::PhysicsComp(float myMass, Entity* myParent):Component("Physics",myParent),mass(myMass)
{
	total_translational_force=Vector2(0,0);
	velocity=Vector2(0,0);
	acceleration=Vector2(0,0);
	rotational_velocity = 0;
	rotational_acceleration = 0;
	total_torque = 0;
}


void PhysicsComp::update(float dt)
{
	PositionComp* pos_comp = (PositionComp*) getComponent("Position");

	//Rotational Movement
	moment_of_inertia = mass;
	rotational_acceleration = total_torque / moment_of_inertia; //TODO: Calc total torque and moment of inertia
																//moment_of_inertia += attached_physics->getMass()*(distance*distance);
	rotational_velocity += rotational_acceleration*dt;
	pos_comp->setRotation(pos_comp->getRotation() + rotational_velocity*dt);

	//Whetehr or not it moves translationally depends on its moment of inertia, forget tangents, period.

	//Planar Movement
	acceleration.x = total_translational_force.x/mass;
	acceleration.y = total_translational_force.y/mass;
	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;
	pos_comp->setPositionX(pos_comp->getPosition().x + velocity.x*dt);
	pos_comp->setPositionY(pos_comp->getPosition().y + velocity.y*dt);

	total_torque = 0; 
	total_translational_force = Vector2 (0,0);
}

void PhysicsComp::addForce(Force myForce)
{
	Vector2 force = Vector2::RadianToVector2(myForce.getRadianDirection());
	force.x = force.x * myForce.getForce();
	force.y = force.y * myForce.getForce();
	total_translational_force+=force;
}
void PhysicsComp::addDisplacedForce(Force myForce)
{
	float distance = Vector2::getDistanceBetween(Vector2(0,0),myForce.getDisplacement());

	float radian_from_center_mass = Vector2::Vector2ToRadian(myForce.getDisplacement());
	float radian_to_center_mass = radian_from_center_mass + 3.1459;

	float attached_direction_displacement = myForce.getRadianDirection() - radian_to_center_mass;

	total_torque += distance *  myForce.getForce() * -sin(myForce.getRadianDirection());

	addForce(myForce);
}