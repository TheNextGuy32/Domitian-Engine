#include "SpaceshipComp.h"

SpaceshipComp::SpaceshipComp(double myArmor, Entity* myParent) 
	: Component("Spaceship", myParent), armor(myArmor)
{

};