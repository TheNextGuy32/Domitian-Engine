#include "PhysicsComp.h"
#include "PositionComp.h"

PhysicsComp::PhysicsComp(float myMass, Entity* myParent):Component("Physics",myParent),mass(myMass)
{

}


void PhysicsComp::update(float dt)
{
	PositionComp* posComp = (PositionComp*) getComponent("Position");

	//Rotational Movement

	/*float radian_from_center_mass = tethered->getDirectionRadian();
	float radian_to_center_mass = radian_from_center_mass + 3.1415926;
	float t = attached_position->getAngle() - radian_to_center_mass ;//moment_of_inertia += attached_physics->getMass()*(distance*distance);
	*/
	//rotational_acceleration = total_torque/moment_of_inertia;
	//rotatonal_velocity += rotational_acceleration*dt;
	//posComp->setRotation(posComp->getRotation() + rotation_velocity*dt);

	//Planar Movement
	acceleration.x = total_force.x/mass;
	acceleration.y = total_force.y/mass;
	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;
	posComp->setPositionX(posComp->getPosition().x - velocity.x*dt);
	posComp->setPositionY(posComp->getPosition().y - velocity.y*dt);
}

void PhysicsComp::addForce(float myRadianDirection, float myNewtons)
{
	Vector2 force = force.RadianToVector2(myRadianDirection);
	force.x = force.x * myNewtons;
	force.y = force.y * myNewtons;
	total_force+=force;
}
void PhysicsComp::addDisplacedForce(Vector2 myDisplacement, float myRadianDirection,float myForce)
{

}