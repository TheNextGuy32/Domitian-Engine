#include "BulletComp.h"

BulletComp::BulletComp(double myArmorPiercing, Entity* myParent) : Component("Bullet",myParent), armor_piercing(myArmorPiercing)
{

};