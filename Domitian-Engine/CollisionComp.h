#ifndef DCollisionComp
#define DCollisionComp

#include "Component.h"
#include "PositionComp.h"

class CollisionComp:public Component
{
public:
	CollisionComp(float,Entity*);
	void update(float);
	float getCollisionRadius()
	{
		return collision_radius;
	};
	static bool checkCollision(CollisionComp*,CollisionComp*);
private:
	float collision_radius;
};

#endif