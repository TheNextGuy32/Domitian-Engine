#include "PositionComp.h"

PositionComp::PositionComp(Vector3 myPosition, float myRotation, Entity* myParent) 
	: Component("Position",myParent), position(myPosition), rotation(myRotation)
{

}

void PositionComp::update(float dt)
{

}

void PositionComp::setPosition(float myX,float myY)
{
	position.x = myX;
	position.y = myY;
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
}