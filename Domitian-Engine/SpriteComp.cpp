#include "SpriteComp.h"
#include "PositionComp.h"

#include <allegro5/bitmap_draw.h>

SpriteComp::SpriteComp(ALLEGRO_BITMAP* myBitmap,Entity* myParent):Component("Sprite",myParent),bitmap(myBitmap)
{

}

void SpriteComp::update(float dt)
{
	PositionComp* positionComp = (PositionComp*) getComponent("Position");

	Vector3 position = positionComp->getPosition();

	al_draw_rotated_bitmap(	bitmap,
							position.x,position.y,
							al_get_bitmap_width(bitmap)/2,al_get_bitmap_height(bitmap)/2,
							positionComp->getRotation(),
							0);
	
	
}