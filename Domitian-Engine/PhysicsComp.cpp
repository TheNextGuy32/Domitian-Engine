#include "PhysicsComp.h"
#include "Radian.h"

PhysicsComp::PhysicsComp(float myMass,float myRadius, Entity* myParent):Component("Physics",myParent),mass(myMass),radius(myRadius)
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
	moment_of_inertia = (2/5) * mass * (radius *radius);
	rotational_acceleration = total_torque / moment_of_inertia; //TODO: Calc total torque and moment of inertia
																//moment_of_inertia += attached_physics->getMass()*(distance*distance);
	rotational_velocity += rotational_acceleration*dt;
	//pos_comp->setRotation(pos_comp->getRotation() + rotational_velocity*dt);

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
	/*float radian_from_center_mass = Vector2::Vector2ToMathRadian(myForce.getDisplacement());
	float radian_to_center_mass = radian_from_center_mass + 3.1459;*/

	//float attached_direction_displacement = myForce.getForceDirection() - radian_to_center_mass;

	//total_torque += radius *  myForce.getForce() * sin(myForce.getMathRadianToForce());

	Vector2 force = Vector2::MathRadianToVector2(myForce.getForceMathRadian());
	force.x = force.x * myForce.getForce();
	force.y = force.y * myForce.getForce();
	total_translational_force+=force;
}

bool PhysicsComp::checkCollision(PhysicsComp* first, PhysicsComp* second)
{
	PositionComp* first_pos_comp = (PositionComp*) first->getComponent("Position");
	Vector2 first_pos = Vector2(first_pos_comp->getPosition().x,first_pos_comp->getPosition().y);

	PositionComp* second_pos_comp = (PositionComp*) second->getComponent("Position");
	Vector2 second_pos = Vector2(second_pos_comp->getPosition().x,second_pos_comp->getPosition().y);

	if( Vector2::getDistanceBetween(first_pos,second_pos) < (first->getRadius()+second->getRadius()))
	{
		return true;
	}

	return false;
}