#ifndef DPosComp_H
#define DPosComp_H

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

#include "Component.h"


//Try including the game object in the cpp file

class PositionComp : public Component
{
public:
	PositionComp(Vector3,double);
	PositionComp(Vector3);


	Vector2 getPosition()
	{
		return Vector2(position.x,position.y);
	};
	void setPosition(double,double);
	void setPositionX(double);
	void setPositionY(double);
	void setDepth(double);

	Vector2 getBucket()
	{
		return Vector2(  floor(position.x / 100), floor(position.y / 100) );
	};

	double getRotation();
	void setRotation(double);

private:
	Vector3 position;
	double rotation;
};
#endif