#include "PhysicsComp.h"
#include "Radian.h"

#define MAX_ROTATION_SPEED 7
#define MAX_TRANSLATION_SPEED 70

PhysicsComp::PhysicsComp(float myMass,float myRadius, Entity* myParent):Component("Physics",myParent),mass(myMass),radius(myRadius)
{
	total_translational_force=Vector2(0,0);
	velocity=Vector2(0,0);
	acceleration=Vector2(0,0);
	rotational_velocity = 0;
	rotational_acceleration = 0;
	total_torque = 0;
	collided =false;

	position_comp = (PositionComp*) getComponent("Position");
}


void PhysicsComp::update(float dt)
{
	collided = false;

	//Rotational Movement
	moment_of_inertia = (2.0/3.0) * mass * (radius * radius);

	rotational_acceleration = total_torque / moment_of_inertia; 
	rotational_velocity += rotational_acceleration*dt;

	//Making sure you dont spin too fast
	if (rotational_velocity>MAX_ROTATION_SPEED)
	{
		rotational_velocity=MAX_ROTATION_SPEED;
	}
	if (rotational_velocity<-MAX_ROTATION_SPEED)
	{
		rotational_velocity=-MAX_ROTATION_SPEED;
	}
	position_comp->setRotation(position_comp->getRotation() + rotational_velocity*dt);

	//Whetehr or not it moves translationally depends on its moment of inertia, forget tangents, period.

	//Planar Movement
	acceleration.x = total_translational_force.x/mass;
	acceleration.y = total_translational_force.y/mass;
	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;

	if(velocity.x > MAX_TRANSLATION_SPEED)
	{
		velocity.x = MAX_TRANSLATION_SPEED;
	}
	if(velocity.y > MAX_TRANSLATION_SPEED)
	{
		velocity.y = MAX_TRANSLATION_SPEED;
	}

	if(velocity.x < -MAX_TRANSLATION_SPEED)
	{
		velocity.x = -MAX_TRANSLATION_SPEED;
	}
	if(velocity.y < -MAX_TRANSLATION_SPEED)
	{
		velocity.y = -MAX_TRANSLATION_SPEED;
	}

	position_comp->setPositionX(position_comp->getPosition().x + velocity.x*dt);
	position_comp->setPositionY(position_comp->getPosition().y + velocity.y*dt);

	total_torque = 0; 
	total_translational_force = Vector2 (0,0);
}

void PhysicsComp::addForce(Force myForce)
{
	float radian_to_center_mass = myForce.getMathRadianToForce() + 3.1459;

	float attached_direction_displacement = myForce.getForceMathRadian() - radian_to_center_mass;

	total_torque += -(radius *  myForce.getForce() * sin(attached_direction_displacement));

	Vector2 force = Vector2::ToVector2(myForce.getForceMathRadian());
	force.x = force.x * myForce.getForce();
	force.y = force.y * myForce.getForce();
	total_translational_force+=force;
}

bool PhysicsComp::checkCollision(PhysicsComp* first, PhysicsComp* second)
{
	/*
	1/2 * m * v^2 = kinetic energy for mass m
	to see if energy is conserved
	right before a collision happens, calculate

	1/2 * m * v^2 for alle objects
	then after the collision
	do it again
	with the new velocities
	and see if the numbers are equal
	oh and i forgot to say that you need to sum up all the energies to get total energy
	//float initialEnergy += 0.5 * first->getMass() * Vector2::ToMathRadian(first->getVelocity())*Vector2::ToMathRadian(first->getVelocity());
	//initialEnergy += 0.5 * second->getMass() * Vector2::ToMathRadian(second->getVelocity())*Vector2::ToMathRadian(second->getVelocity());

	the v^2 outputs a scalar so it works for any number of components
	*/

	PositionComp* first_pos_comp = (PositionComp*) first->getComponent("Position");
	Vector2 first_pos = Vector2(first_pos_comp->getPosition().x,first_pos_comp->getPosition().y);

	PositionComp* second_pos_comp = (PositionComp*) second->getComponent("Position");
	Vector2 second_pos = Vector2(second_pos_comp->getPosition().x,second_pos_comp->getPosition().y);

	float distanceBetween = Vector2::getDistanceBetween(first_pos,second_pos);
	float addingRadii = first->getRadius()+second->getRadius();

	if(!first->getCollided() || !second->getCollided())
	{
		//Collision
		if( distanceBetween < addingRadii)
		{
			first->setCollided(true);
			second->setCollided(true);

			//Magnitude is multiplied by ratio
			Vector2 displacement = Vector2(	second_pos_comp->getPosition().x - first_pos_comp->getPosition().x,
				second_pos_comp->getPosition().y - first_pos_comp->getPosition().y);

			float mathRadianDirectionTo = Vector2::ToMathRadian(displacement);
			Vector2 normalizedDirectionTo = Vector2(displacement.x/distanceBetween,displacement.y/distanceBetween);

			//The force applied to second = magnitude of speed of first * its mass
			float first_force_exerted = (Vector2::getDistanceBetween(Vector2(0,0),first->getVelocity())) * first->getMass();
			float second_force_exerted = Vector2::getDistanceBetween(Vector2(0,0),second->getVelocity()) * second->getMass();
			float net_force = first_force_exerted+second_force_exerted;

			//Adding the forces
			first->addForce(Force (mathRadianDirectionTo,  Vector2::ToMathRadian(second->getVelocity())     ,net_force));
			second->addForce(Force (mathRadianDirectionTo+3.1459, 3.1459+Vector2::ToMathRadian(first->getVelocity()),net_force));
			
			float push = (addingRadii-distanceBetween)/2;

			first_pos_comp->setPosition( first_pos.x - normalizedDirectionTo.x*push, first_pos.y - normalizedDirectionTo.y*push);
			second_pos_comp->setPosition( second_pos.x + normalizedDirectionTo.x*push, second_pos.y + normalizedDirectionTo.y*push);


			return true;
		}
		return false;
	}
	return false;
}