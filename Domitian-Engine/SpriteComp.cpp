#include "SpriteComp.h"

SpriteComp::SpriteComp(ALLEGRO_BITMAP* myBitmap,Entity* myParent):Component("Sprite",myParent),bitmap(myBitmap)
{

}

void SpriteComp::update(float dt)
{

}