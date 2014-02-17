//Duration before fire another round

#ifndef Turret_Comp_H
#define TurretComp_H

#include "Component.h"

class TurretComp : public Component
{
public:
	TurretComp(double myBulletWeight, double myBulletForce, double myArmorPiercing, double myReloadTime, Entity* myParent);

	double getBulletWeight(){return bullet_weight;};
	double getBulletForce(){return bullet_force;};
	double getBulletArmorPiercing(){return bullet_armor_piercing;};

	bool canFire();

	void update(double dt);

private:
	double bullet_weight;
	double bullet_force;
	double bullet_armor_piercing; 

	double curret_reload_time;
	double max_reload_time;
};

#endif