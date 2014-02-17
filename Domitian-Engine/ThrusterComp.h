#ifndef ThrusterComp_H
#define ThrusterComp_H

#include "Component.h"

class ThrusterComp : public Component
{
public:
	ThrusterComp(double myForceExerted, Entity* myParent);

	double getForceExerted();

private:
	double force_exerted;
};

#endif