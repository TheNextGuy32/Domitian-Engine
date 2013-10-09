#ifndef DPhysicsComp_H
#define DPhysicsComp_H

#include "Component.h"
#include "PositionComp.h"
#include "Force.h"

#include <vector>

class PhysicsComp : public Component
{
public:
	PhysicsComp(float, Entity*);

    void update(float);

	void addForce(Force myForce);
	void addDisplacedForce(Force myForce);

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
	}

	float getDistanceBetween(float x, float y, float x1, float y1)
	{
		return sqrt((x1-x)*(x1-x) + (y1-y)*(y1-y));
	};

private:
	float mass;

	Vector2 total_translational_force;
	std::vector<Force> displaced_forces;
	Vector2 velocity;
	Vector2 acceleration;

	float total_torque;
	float rotational_velocity;
	float rotational_acceleration;
};
#endif

