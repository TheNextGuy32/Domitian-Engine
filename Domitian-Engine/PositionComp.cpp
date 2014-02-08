#include "PositionComp.h"

PositionComp::PositionComp(Vector3 myPosition, float myRotation, Entity* myParent) 
	: Component("Position",myParent), position(myPosition), rotation(myRotation)
{
}

PositionComp::PositionComp(Vector3 myPosition, Entity* myParent) 
	: Component("Position",myParent), position(myPosition), rotation(0)
{
}

void PositionComp::setPosition(float myX,float myY)
{
	position.x = myX;
	position.y = myY;

}
float PositionComp::getRotation()
{
	return rotation;
}

void PositionComp::setPositionX(float myX)
{
	position.x = myX;

}
void PositionComp::setPositionY(float myY)
{
	position.y = myY;

}

void PositionComp::setDepth(float myDepth)
{
	position.z = myDepth;
}

void PositionComp::setRotation(float myRot)
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