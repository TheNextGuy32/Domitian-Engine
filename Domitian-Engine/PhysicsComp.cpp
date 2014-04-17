#include "PhysicsComp.h"
#include "Radian.h"

#define MAX_ROTATION_SPEED 7
#define MAX_TRANSLATION_SPEED 70

PhysicsComp::PhysicsComp(double myMass,double myRadius,double myCofRestitution,PositionComp* myPosComp):Component("Physics"),mass(myMass),radius(myRadius),coefficient_of_restitution(myCofRestitution)
{
	total_translational_force=Vector2(0,0);
	velocity=Vector2(0,0);
	acceleration=Vector2(0,0);
	rotational_velocity = 0;
	rotational_acceleration = 0;
	total_torque = 0;
	collided =false;

	position_comp = myPosComp;
}

void PhysicsComp::update(double dt)
{
	collided = false;

	bool rotational_movement = true;
	bool planar_movement =true;

	//Rotational Movement
	if(rotational_movement)
	{
		//Rotational Movement
		moment_of_inertia = (2.0/5.0) * mass * (radius * radius);

		rotational_acceleration = (total_torque) / moment_of_inertia; 
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

	double attached_direction_displacement = myForce.getForceDirectionMathRadian() - radian_to_center_mass;

	total_torque += -(radius *  myForce.getForce() * sin(attached_direction_displacement));

	Vector2 force_normal_components = Vector2::ToVector2(myForce.getForceDirectionMathRadian());
	Vector2 translation (force_normal_components.x * myForce.getForce() * cos(attached_direction_displacement),
		force_normal_components.y * myForce.getForce() * cos(attached_direction_displacement));
	total_translational_force+=translation;
}

void PhysicsComp::addForceWithRadius(Force myForce, float myRadius)
{
	double radian_to_center_mass = myForce.getMathRadianToForce() + PI;

	double attached_direction_displacement = myForce.getForceDirectionMathRadian() - radian_to_center_mass;

	total_torque += -(myRadius *  myForce.getForce() * sin(attached_direction_displacement));

	Vector2 force_normal_components = Vector2::ToVector2(myForce.getForceDirectionMathRadian());
	Vector2 translation (force_normal_components.x * myForce.getForce() * cos(attached_direction_displacement),
		force_normal_components.y * myForce.getForce() * cos(attached_direction_displacement));
	total_translational_force+=translation;
}

double squared(double myInput)
{
	return myInput*myInput;
};

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

	bool push_enabled = false;

	bool collision = false;

	//Check for previosu collision
	if(!first->getCollided() || !second->getCollided())
	{
		//Pull the objects positions
		PositionComp* first_pos_comp = (PositionComp*) first->getComponent("Position");
		PhysicsComp* first_phys_comp = (PhysicsComp*) first->getComponent("Physics");
		Vector2 first_pos = Vector2(first_pos_comp->getPosition().x,first_pos_comp->getPosition().y);

		PositionComp* second_pos_comp = (PositionComp*) second->getComponent("Position");
		PhysicsComp* second_phys_comp = (PhysicsComp*) second->getComponent("Physics");
		Vector2 second_pos = Vector2(second_pos_comp->getPosition().x,second_pos_comp->getPosition().y);

		//Find the distance and added radii
		double distanceBetween = Vector2::getDistanceBetween(first_pos,second_pos);
		
		double addingRadii = first->getRadius()+second->getRadius();

		//Collision
		if(distanceBetween < addingRadii)
		{
			double radian_from_horizontal_to_second = Vector2::ToMathRadian((Vector2(second_pos.x-first_pos.x,second_pos.y-first_pos.y)));

			//Make sure it doesnt collide with anythign else this tick
			first->setCollided(true);
			second->setCollided(true);

			//Magnitude is multiplied by ratio
			Vector2 displacement = Vector2(	second_pos_comp->getPosition().x - first_pos_comp->getPosition().x,
				second_pos_comp->getPosition().y - first_pos_comp->getPosition().y);

			double mathRadianDirectionTo = Vector2::ToMathRadian(displacement);
			Vector2 normalizedDirectionTo = Vector2(displacement.x/distanceBetween,displacement.y/distanceBetween);


			//Mass and acceleration
			double first_mass = first_phys_comp->getMass();
			Vector2 first_velocity = first_phys_comp->getVelocity();

			double second_mass = second_phys_comp->getMass();
			Vector2 second_velocity = second_phys_comp->getVelocity();

			//1 is elastic, 0 is inelastic
			double first_CoR = first_phys_comp->getCoefficientOfRestitution();
			double second_CoR = second_phys_comp->getCoefficientOfRestitution();
			double coefficient_of_restitution = (first_CoR+second_CoR)/2.0;

			//One dimensional solution with elasticity
			double both_masses= first_mass + second_mass;

			first_phys_comp->setVelocity(Vector2(
				((coefficient_of_restitution*second_mass*(second_velocity.x-first_velocity.x))+(first_mass*first_velocity.x)+(second_mass*second_velocity.x))/(second_mass+first_mass),
				((coefficient_of_restitution*second_mass*(second_velocity.y-first_velocity.y))+(first_mass*first_velocity.y)+(second_mass*second_velocity.y))/(second_mass+first_mass)
				));

			second_phys_comp->setVelocity(Vector2(
				((coefficient_of_restitution*first_mass*(first_velocity.x-second_velocity.x))+(second_mass*second_velocity.x)+(first_mass*first_velocity.x))/(first_mass+second_mass),
				((coefficient_of_restitution*first_mass*(first_velocity.y-second_velocity.y))+(second_mass*second_velocity.y)+(first_mass*first_velocity.y))/(first_mass+second_mass)
				));

			//Ramons solution is still one dimensional
			/*first_phys_comp->setVelocity(Vector2(
				((second_mass*(2*(second_velocity.x-first_velocity.x))) +(first_mass*first_phys_comp->getVelocity().x))/both_masses,
				((second_mass*(2*(second_velocity.y-first_velocity.y))) +(first_mass*first_phys_comp->getVelocity().y))/both_masses
				));

			second_phys_comp->setVelocity(Vector2(
				((first_mass*(2*(first_velocity.x-second_velocity.x))) +(second_mass*second_phys_comp->getVelocity().x))/both_masses,
				((first_mass*(2*(first_velocity.y-second_velocity.y))) +(second_mass*second_phys_comp->getVelocity().y))/both_masses
				));*/

			

			////The force applied to second = magnitude of speed of first * its mass
			////Does the force it exerts on the other object depend on the direction its facing
			////	for instance, say the other object is moving away from the other oject, it wouldn't be applying that big of a force
			double first_momentum = Vector2::getDistanceBetween(Vector2(0,0),first->getVelocity()) * first->getMass();
			double second_momentum = Vector2::getDistanceBetween(Vector2(0,0),second->getVelocity()) * second->getMass();
			double net_force = first_momentum+second_momentum;

			double first_additional_torque = -(first_phys_comp->radius *  net_force * sin(mathRadianDirectionTo - Vector2::ToMathRadian(second->getVelocity())));
			first_phys_comp->total_torque+= first_additional_torque;

			double second_additional_torque = -(second_phys_comp->radius *  net_force * sin(mathRadianDirectionTo + PI - Vector2::ToMathRadian(first->getVelocity())));
			second_phys_comp->total_torque += second_additional_torque;

			////Adding the forces, other object gets force in direction that other was moving
			//first->addForce(Force (mathRadianDirectionTo,  Vector2::ToMathRadian(second->getVelocity()), net_force));
			//second->addForce(Force (mathRadianDirectionTo+PI, Vector2::ToMathRadian(first->getVelocity()), net_force));


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
