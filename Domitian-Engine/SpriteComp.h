#ifndef DSpriteComp_H
#define DSpriteComp_H

#include "Component.h"
#include "PositionComp.h"
#include "Radian.h"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap.h>



//Try including the game object in the cpp file

class SpriteComp : public Component
{
public:
	SpriteComp(ALLEGRO_BITMAP*,Entity*);

	ALLEGRO_BITMAP* getBitmap()
	{
		return bitmap;
	};
	void setBitmap(ALLEGRO_BITMAP* newBitmap)
	{
		bitmap = newBitmap;
	};
	void update(float);
private:
	PositionComp* positionComp;
	ALLEGRO_BITMAP* bitmap;
	Vector2 offset;
};
#endif