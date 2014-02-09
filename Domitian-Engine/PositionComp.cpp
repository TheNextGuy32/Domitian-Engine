#include "PositionComp.h"

PositionComp::PositionComp(Vector3 myPosition, double myRotation, Entity* myParent) 
	: Component("Position",myParent), position(myPosition), rotation(myRotation)
{
}

PositionComp::PositionComp(Vector3 myPosition, Entity* myParent) 
	: Component("Position",myParent), position(myPosition), rotation(0)
{
}

void PositionComp::setPosition(double myX,double myY)
{
	position.x = myX;
	position.y = myY;

}
double PositionComp::getRotation()
{
	return rotation;
}

void PositionComp::setPositionX(double myX)
{
	position.x = myX;

}
void PositionComp::setPositionY(double myY)
{
	position.y = myY;

}

void PositionComp::setDepth(double myDepth)
{
	position.z = myDepth;
}

void PositionComp::setRotation(double myRot)
{
	rotation = myRot;
	while(abs(rotation)>(3.14159265359*2))
	{
		if(rotation>0)
		{
			rotation-=3.14159265359*2;
		}
		if(rotation<0)
		{
			rotation+=3.14159265359*2;
		}
	}
}