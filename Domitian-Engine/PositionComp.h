#ifndef DPosComp_H
#define DPosComp_H

#include "Component.h"


//Try including the game object in the cpp file

class PositionComp : public Component
{
public:
	PositionComp(Vector3,float,Entity*);
	
	void update(float);

	Vector3 getPosition()
	{
		return position;
	};
	void setPosition(float,float);
	void setPositionX(float);
	void setPositionY(float);
	void setDepth(float);

	float getRotation()
	{
		return rotation;
	};
	void setRotation(float);

private:
	Vector3 position;
	float rotation;
};
#endif