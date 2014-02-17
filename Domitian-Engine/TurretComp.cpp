#include "TurretComp.h"

TurretComp::TurretComp(double myBulletWeight, double myBulletForce, double myArmorPiercing,double myReloadTime, Entity* myParent)
	: Component("Turret",myParent),
	bullet_weight(myBulletWeight), bullet_force(myBulletForce), bullet_armor_piercing(myArmorPiercing),max_reload_time(myReloadTime)
{
};

bool TurretComp::canFire()
{
	if(curret_reload_time>max_reload_time)
	{
		curret_reload_time = 0;
		return true;	
	}
	else return false;
};

void TurretComp::update(double dt)
{
	if(curret_reload_time<max_reload_time)
	{
		curret_reload_time+=dt;
	}
};