//The combustibility of this

#ifndef BulletComp_H
#define BulletComp_H

#include "Component.h"

class BulletComp : public Component
{
public:
	BulletComp(double myArmorPiercing);

	double getArmorPiercing(){return armor_piercing;};

private:
	double armor_piercing;
};

#endif