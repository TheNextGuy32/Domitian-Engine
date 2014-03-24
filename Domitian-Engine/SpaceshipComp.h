#ifndef SpaceshipComp_H
#define SpaceshipComp_H

#include "Component.h"

class SpaceshipComp : public Component
{
public:
	SpaceshipComp(double myArmor);

	double getArmor(){return armor;}
private:
	double armor;
};

#endif