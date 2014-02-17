#ifndef SpaceshipComp_H
#define SpaceshipComp_H

#include "Component.h"

class SpaceshipComp : public Component
{
public:
	SpaceshipComp(double myArmor, Entity* myParent);

	double getArmor(){return armor;}
private:
	double armor;
};

#endif