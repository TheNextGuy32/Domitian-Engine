#ifndef DPhysicsComp_H
#define DPhysicsComp_H

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#include "Component.h"
#include "PositionComp.h"
#include "Force.h"

#include <vector>

class PhysicsComp : public Component
{
public:
	PhysicsComp(double myMass,double myRadius,double myCofRestitution,PositionComp* myPosComp);

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

	double getCoefficientOfRestitution()
	{
		return coefficient_of_restitution;
	};
	
private:

	PositionComp* position_comp;

	bool collided;
	
	double mass;
	double moment_of_inertia;

	double radius;

	double coefficient_of_restitution;

	Vector2 total_translational_force;
	Vector2 velocity;
	Vector2 acceleration;

	double total_torque;
	double rotational_velocity;
	double rotational_acceleration;

	
};
#endif

