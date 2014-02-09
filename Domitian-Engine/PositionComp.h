#ifndef DPosComp_H
#define DPosComp_H

#include "Component.h"


//Try including the game object in the cpp file

class PositionComp : public Component
{
public:
	PositionComp(Vector3,double,Entity*);
	PositionComp(Vector3,Entity*);


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