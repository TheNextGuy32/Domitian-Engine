#ifndef DForce
#define DForce

class Force
{
public:
	Force(float myDirectionToForce,float myForceDirection, float myForce);

	float getMathRadianToForce()
	{
		return direction_to_force;
	};

	float getForceMathRadian()
	{
		return force_direction;
	};

	float getForce()
	{
		return force;
	};

private:
	float direction_to_force;
	float force_direction;
	float force;

};
#endif