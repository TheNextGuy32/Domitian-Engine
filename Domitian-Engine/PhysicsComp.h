#ifndef DPhysicsComp_H
#define DPhysicsComp_H

#include "Component.h"

class PhysicsComp : public Component
{
public:
	PhysicsComp(float, Entity*);

    void update(float);

	void addForce(Vector2 myForce)
	{
		total_force+=myForce;
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
	float rotational_velocity;
	Vector2 acceleration;
	float rotational_acceleration;
};
#endif

