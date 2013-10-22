#include "SpriteComp.h"




SpriteComp::SpriteComp(ALLEGRO_BITMAP* myBitmap,Entity* myParent):Component("Sprite",myParent),bitmap(myBitmap)
{
	offset = Vector2 (al_get_bitmap_width(bitmap)/2,al_get_bitmap_height(bitmap)/2);
}

void SpriteComp::update(float dt)
{
	PositionComp* positionComp = (PositionComp*) getComponent("Position");

	al_draw_rotated_bitmap(	bitmap,
							offset.x,offset.y,
							positionComp->getPosition().x,-positionComp->getPosition().y,
							positionComp->getRotation()-(3.1459/2), 
							0);
	
}