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

	Vector2 getVelocity()
	{
		return velocity;
	};

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

	static bool checkCollision(PhysicsComp* first, PhysicsComp* second);

	bool getCollided()
	{
		return collided;
	};
	void setCollided(bool myCollided)
	{
		collided = myCollided;
	};

private:
	PositionComp* position_comp;

	bool collided;
	
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

