#include "PhysicsComp.h"
#include "Radian.h"

#define MAX_ROTATION_SPEED 7
#define MAX_TRANSLATION_SPEED 70

PhysicsComp::PhysicsComp(double myMass,double myRadius, Entity* myParent):Component("Physics",myParent),mass(myMass),radius(myRadius)
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

void PhysicsComp::update(double dt)
{
	collided = false;

	bool rotational_movement = true;
	bool planar_movement = false;

	//Rotational Movement
	if(rotational_movement)
	{
		//Rotational Movement
		moment_of_inertia = (2.0/3.0) * mass * (radius * radius);

		rotational_acceleration = (total_torque/2) / moment_of_inertia; 
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

		total_torque = 0; 
	}

	//Planar Movement
	if(planar_movement)
	{
		acceleration.x = total_translational_force.x/mass;
		acceleration.y = total_translational_force.y/mass;
		velocity.x += acceleration.x * dt;
		velocity.y += acceleration.y * dt;

		//																			      //
		//If the mag of the vector is too massive then we reduce and recalc the components//
		//																				  //
		/*double vector_magnitude = sqrt((velocity.x*velocity.x)+(velocity.y*velocity.y));
		if (vector_magnitude>MAX_TRANSLATION_SPEED)
		{
		vector_magnitude = MAX_TRANSLATION_SPEED;
		}
		else if(vector_magnitude<-MAX_TRANSLATION_SPEED)
		{
		vector_magnitude = -MAX_TRANSLATION_SPEED;
		}
		velocity.x = cos(position_comp->getRotation()) * vector_magnitude;
		velocity.y = sin(position_comp->getRotation()) * vector_magnitude;
		*/

		position_comp->setPositionX(position_comp->getPosition().x + velocity.x*dt);
		position_comp->setPositionY(position_comp->getPosition().y + velocity.y*dt);

		total_translational_force = Vector2 (0,0);
	}
}

void PhysicsComp::addForce(Force myForce)
{
	double radian_to_center_mass = myForce.getMathRadianToForce() + PI;

	double attached_direction_displacement = myForce.getForceMathRadian() - radian_to_center_mass;

	total_torque += -(radius *  myForce.getForce() * sin(attached_direction_displacement));

	Vector2 force_normal_components = Vector2::ToVector2(myForce.getForceMathRadian());
	Vector2 translation (force_normal_components.x * myForce.getForce(),force_normal_components.y * myForce.getForce());
	total_translational_force+=translation;
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
	//double initialEnergy += 0.5 * first->getMass() * Vector2::ToMathRadian(first->getVelocity())*Vector2::ToMathRadian(first->getVelocity());
	//initialEnergy += 0.5 * second->getMass() * Vector2::ToMathRadian(second->getVelocity())*Vector2::ToMathRadian(second->getVelocity());

	the v^2 outputs a scalar so it works for any number of components
	*/

	bool push_enabled = true;
	bool buckets_enabled = false;


	bool collision = false;

	//Check for previosu collision
	if(!first->getCollided() || !second->getCollided())
	{
		//Pull the objects positions
		PositionComp* first_pos_comp = (PositionComp*) first->getComponent("Position");
		PositionComp* second_pos_comp = (PositionComp*) second->getComponent("Position");

		//Check if we are within at least 2 buckets of it, for large objects that straddle mutliple buckets
		if(buckets_enabled)
		{
			if(abs(first_pos_comp->getBucket().x - second_pos_comp->getBucket().x)<1)
			{
				if(abs(first_pos_comp->getBucket().y - second_pos_comp->getBucket().y)<1)
				{
				}
			}
		}
		//Pull the physics and positions of the objects
		PhysicsComp* first_phys_comp = (PhysicsComp*) first->getComponent("Physics");
		Vector2 first_pos = Vector2(first_pos_comp->getPosition().x,first_pos_comp->getPosition().y);

		PhysicsComp* second_phys_comp = (PhysicsComp*) second->getComponent("Physics");
		Vector2 second_pos = Vector2(second_pos_comp->getPosition().x,second_pos_comp->getPosition().y);

		//Find the distance and added radii
		double distanceBetween = Vector2::getDistanceBetween(first_pos,second_pos);
		double addingRadii = first->getRadius()+second->getRadius();

		//Collision
		if(distanceBetween < addingRadii)
		{
			//Make sure it doesnt collide with anythign else this tick
			first->setCollided(true);
			second->setCollided(true);

			//Magnitude is multiplied by ratio
			Vector2 displacement = Vector2(	second_pos_comp->getPosition().x - first_pos_comp->getPosition().x,
				second_pos_comp->getPosition().y - first_pos_comp->getPosition().y);

			double mathRadianDirectionTo = Vector2::ToMathRadian(displacement);
			Vector2 normalizedDirectionTo = Vector2(displacement.x/distanceBetween,displacement.y/distanceBetween);

			//The force applied to second = magnitude of speed of first * its mass
			//Does the force it exerts on the other object depend on the direction its facing
			//	for instance, say the other object is moving away from the other oject, it wouldn't be applying that big of a force
			double first_force_exerted = Vector2::getDistanceBetween(Vector2(0,0),first->getVelocity()) * first->getMass();
			double second_force_exerted = Vector2::getDistanceBetween(Vector2(0,0),second->getVelocity()) * second->getMass();
			double net_force = first_force_exerted+second_force_exerted;

			//Adding the forces, other object gets force in direction that other was moving
			first->addForce(Force (mathRadianDirectionTo,  Vector2::ToMathRadian(second->getVelocity()), net_force));
			second->addForce(Force (mathRadianDirectionTo+PI, Vector2::ToMathRadian(first->getVelocity()), net_force));
			

			//IF BALL 2 IS NOT MOVING
			//Final Velocity x of the first object = ((m1-m2)/m1+m2) * v1x
			//F Vel x of the second objet = (2m1/m1+m2) * v1x i  
			//Same applies for y direction



			//The amount the lesser mass gets pushed so they are overlapping


			//ANTI TUNNELING
			if(push_enabled)
			{
				//Add 1 to push so that you arent perma colliding
				double push = std::abs(addingRadii+1-distanceBetween);

				if(first_phys_comp->getMass()<second_phys_comp->getMass())
				{
					first_pos_comp->setPosition( first_pos.x - normalizedDirectionTo.x*push, first_pos.y - normalizedDirectionTo.y*push);
				}
				else if(first_phys_comp->getMass()>second_phys_comp->getMass())
				{
					second_pos_comp->setPosition( second_pos.x + normalizedDirectionTo.x*push, second_pos.y + normalizedDirectionTo.y*push);
				}
				else

				{
					second_pos_comp->setPosition( second_pos.x + normalizedDirectionTo.x*(push/2), second_pos.y + normalizedDirectionTo.y*(push/2));
					first_pos_comp->setPosition( first_pos.x - normalizedDirectionTo.x*(push/2), first_pos.y - normalizedDirectionTo.y*(push/2));
				}
			}

			return true;
		}
		return false;
	}
	return false;
}