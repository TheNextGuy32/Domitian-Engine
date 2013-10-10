#ifndef DAnimatedComp_H
#define DAnimatedComp_H

#include "Component.h"
#include "PositionComp.h"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap.h>

//Try including the game object in the cpp file

class AnimatedComp : public Component
{
public:
	AnimatedComp(ALLEGRO_BITMAP*,Vector2,Entity*);
	void update(float);

	void setFrameX(float);
	void setFrameY(float);

	void setAnimating(bool myTruth)
	{
		animating = myTruth;
	};

private:
	bool animating;

	ALLEGRO_BITMAP* bitmap;
	
	Vector2 dimensions;
	Vector2 frame;
	Vector2 offset;
	
	Vector2 frames;

private:
};
#endif