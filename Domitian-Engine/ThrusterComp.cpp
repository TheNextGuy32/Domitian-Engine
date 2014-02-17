#include "ThrusterComp.h"

ThrusterComp::ThrusterComp(double myForceExerted, Entity* myParent)
	: Component("Thruster",myParent),force_exerted(myForceExerted)
{
};

double ThrusterComp::getForceExerted()
{
	return force_exerted;
};