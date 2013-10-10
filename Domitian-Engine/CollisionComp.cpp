#include "CollisionComp.h"

CollisionComp::CollisionComp(float myCollisionRadius,Entity* myParent):Component("Collision",myParent)
{
	collision_radius = myCollisionRadius;
}
void CollisionComp::update(float dt)
{

}
bool CollisionComp::checkCollision(CollisionComp* first, CollisionComp* second)
{
	PositionComp* first_pos_comp = (PositionComp*) first->getComponent("Position");
	Vector2 first_pos = Vector2(first_pos_comp->getPosition().x,first_pos_comp->getPosition().y);

	PositionComp* second_pos_comp = (PositionComp*) second->getComponent("Position");
	Vector2 second_pos = Vector2(second_pos_comp->getPosition().x,second_pos_comp->getPosition().y);

	if( Vector2::getDistanceBetween(first_pos,second_pos) < (first->getCollisionRadius()+second->getCollisionRadius()))
	{
		return true;
	}

	return false;
}
