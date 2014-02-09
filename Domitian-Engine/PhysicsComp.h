#ifndef DPhysicsComp_H
#define DPhysicsComp_H

#include "Component.h"
#include "PositionComp.h"
#include "Force.h"

#include <vector>

class PhysicsComp : public Component
{
public:
	PhysicsComp(double,double, Entity*);

    void update(double);

	void addForce(Force myForce);

	Vector2 getVelocity()
	{
		return velocity;
	};

	void setVelocity(Vector2 myVelocity)
	{
		velocity = myVelocity;
	};
	void setRotationalVelocity(double myRot)
	{
		rotational_velocity = myRot;
	};

	double getMass()
	{
		return mass;	
	}
	void setMass(double myMass)
	{
		mass = myMass;
	};
	double getRadius()
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
	
	double mass;
	double moment_of_inertia;

	double radius;

	Vector2 total_translational_force;
	Vector2 velocity;
	Vector2 acceleration;

	double total_torque;
	double rotational_velocity;
	double rotational_acceleration;
};
#endif

