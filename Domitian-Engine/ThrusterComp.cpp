#include "ThrusterComp.h"

ThrusterComp::ThrusterComp(double myForceExerted)
	: Component("Thruster"),force_exerted(myForceExerted)
{
};

double ThrusterComp::getForceExerted()
{
	return force_exerted;
};