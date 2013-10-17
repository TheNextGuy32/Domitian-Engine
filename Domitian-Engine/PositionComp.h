#ifndef DPosComp_H
#define DPosComp_H

#include "Component.h"


//Try including the game object in the cpp file

class PositionComp : public Component
{
public:
	PositionComp(Vector3,float,Entity*);

	Vector2 getPosition()
	{
		return Vector2(position.x,position.y);
	};
	void setPosition(float,float);
	void setPositionX(float);
	void setPositionY(float);
	void setDepth(float);

	Vector2 getBucket()
	{
		return Vector2(  floor(position.x / 200), floor(position.y / 200) );
	};

	float getRotation();
	void setRotation(float);

private:
	Vector3 position;
	float rotation;
};
#endif