#include "SpriteComp.h"




SpriteComp::SpriteComp(ALLEGRO_BITMAP* myBitmap,Entity* myParent):Component("Sprite",myParent),bitmap(myBitmap)
{
	offset = Vector2 (al_get_bitmap_width(bitmap)/2,al_get_bitmap_height(bitmap)/2);
	positionComp = (PositionComp*) getComponent("Position");
}

void SpriteComp::update(float dt)
{

	al_draw_rotated_bitmap(	bitmap,
							offset.x,offset.y,
							positionComp->getPosition().x,-positionComp->getPosition().y,
							Radian::convertToGame(positionComp->getRotation()), 
							0);
	
}