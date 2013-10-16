#ifndef DPhysicsComp_H
#define DPhysicsComp_H

#include "Component.h"
#include "PositionComp.h"
#include "Force.h"

#include <vector>

class PhysicsComp : public Component
{
public:
	PhysicsComp(float,float, Entity*);

    void update(float);

	void addForce(Force myForce);

	void setVelocity(Vector2 myVelocity)
	{
		velocity = myVelocity;
	};
	void setRotationalVelocity(float myRot)
	{
		rotational_velocity = myRot;
	};

	float getMass()
	{
		return mass;	
	}
	void setMass(float myMass)
	{
		mass = myMass;
	};
	float getRadius()
	{
		return radius;
	}

	bool checkCollision(PhysicsComp* first, PhysicsComp* second);

private:
	float mass;
	float moment_of_inertia;

	float radius;

	Vector2 total_translational_force;
	Vector2 velocity;
	Vector2 acceleration;

	float total_torque;
	float rotational_velocity;
	float rotational_acceleration;
};
#endif

