#ifndef DSpriteComp_H
#define DSpriteComp_H

#include "Component.h"
#include "PositionComp.h"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap.h>



//Try including the game object in the cpp file

class SpriteComp : public Component
{
public:
	SpriteComp(ALLEGRO_BITMAP*,Entity*);
	void update(float);
private:
	ALLEGRO_BITMAP* bitmap;
	Vector2 offset;
};
#endif