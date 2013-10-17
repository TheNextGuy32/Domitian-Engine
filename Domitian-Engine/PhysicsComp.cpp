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
	moment_of_inertia = (2.0/5.0) * mass * (radius *radius);
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
	//float radian_from_center_mass = Vector2::Vector2ToMathRadian(myForce.getDisplacement());
	float radian_to_center_mass = myForce.getMathRadianToForce() + 3.1459;

	float attached_direction_displacement = myForce.getForceMathRadian() - radian_to_center_mass;

	total_torque += radius *  myForce.getForce() * sin(attached_direction_displacement);

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

	float distanceBetween = Vector2::getDistanceBetween(first_pos,second_pos);
	float addingRadii = first->getRadius()+second->getRadius();

	if( distanceBetween < addingRadii)
	{
		Vector2 displacement = Vector2(	first_pos_comp->getPosition().x - second_pos_comp->getPosition().x,
			first_pos_comp->getPosition().y - second_pos_comp->getPosition().y);

		//Vector2 collision_push = Vector2(displacement.x/5,displacement.y/5);
		Vector2 collision_push = Vector2(0,0);
		
		float first_force_exerted = Vector2::getDistanceBetween(Vector2(0,0),first->getVelocity()) * first->getMass();
		float second_force_exerted = Vector2::getDistanceBetween(Vector2(0,0),second->getVelocity()) * second->getMass();

		float mathRadianDirectionTo = Vector2::Vector2ToMathRadian(displacement);

		Force first_force (mathRadianDirectionTo,Vector2::Vector2ToMathRadian(second->getVelocity()),first_force_exerted * 10);
		Force second_force (mathRadianDirectionTo + 3.1459 , Vector2::Vector2ToMathRadian(first->getVelocity()),second_force_exerted*10);

		first->addForce(first_force);
		second->addForce(second_force);

		first_pos_comp->setPosition( first_pos_comp->getPosition().x + collision_push.x, 
			first_pos_comp->getPosition().y + collision_push.y);

		second_pos_comp->setPosition(second_pos_comp->getPosition().x - collision_push.x,
		second_pos_comp->getPosition().y - collision_push.y);

		return true;
	}

	return false;
}