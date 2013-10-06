#ifndef DPhysicsComp_H
#define DPhysicsComp_H

#include "Component.h"

class PhysicsComp : public Component
{
public:
	PhysicsComp(float, Entity*);

    void update(float);

	void addForce(float myRadianDirection, float myNewtons);
	void addDisplacedForce(Vector2 myDisplacement, float myRadianDirection,float myNewtons);

	void setVelocity(Vector2 myVelocity)
	{
		velocity = myVelocity;
	}

	float getMass()
	{
		return mass;	
	}
	void setMass(float myMass)
	{
		mass = myMass;
	}

private:
	float mass;

	Vector2 total_force;
	Vector2 velocity;
	Vector2 acceleration;

	float total_torque;
	float rotational_velocity;
	float rotational_acceleration;
};
#endif

