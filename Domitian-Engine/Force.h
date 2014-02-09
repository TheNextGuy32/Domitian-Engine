#ifndef DForce
#define DForce

class Force
{
public:
	Force(double myDirectionToForce,double myForceDirection, double myForce);

	double getMathRadianToForce()
	{
		return direction_to_force;
	};

	double getForceMathRadian()
	{
		return force_direction;
	};

	double getForce()
	{
		return force;
	};

private:
	double direction_to_force;
	double force_direction;
	double force;

};
#endif