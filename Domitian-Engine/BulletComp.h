//The combustibility of this

#ifndef BulletComp_H
#define BulletComp_H

#include "Component.h"

class BulletComp : public Component
{
public:
	BulletComp(double myArmorPiercing, Entity* myParent);

	double getArmorPiercing(){return armor_piercing;};

private:
	double armor_piercing;
};

#endif