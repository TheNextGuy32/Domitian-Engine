#include "AnimatedComp.h"

AnimatedComp::AnimatedComp(ALLEGRO_BITMAP* myBitmap,Vector2 myDimensions, Entity* myParent)
	:Component("Animated",myParent),bitmap(myBitmap),dimensions(myDimensions)
{
	offset = Vector2 (dimensions.x/2,dimensions.y/2);
	frame = Vector2(0,0);
	frames = Vector2 (al_get_bitmap_width(bitmap)/dimensions.x,al_get_bitmap_height(bitmap)/dimensions.y);
}

void AnimatedComp::setFrameX(float x)
{
	if(x>0&& x < frames.x)
	{
		frame.x = x;
	}
}

void AnimatedComp::setFrameY(float y)
{
	if(y>0&&y<frames.y)
	{
		frame.y = y;
	}
}

void AnimatedComp::update(float dt)
{
	PositionComp* positionComp = (PositionComp*) getComponent("Position");

	Vector3 position = positionComp->getPosition();

	al_draw_scaled_bitmap(	bitmap, 
							frame.x * dimensions.x, frame.y * dimensions.y,//Where to start within bitmap
							dimensions.x, dimensions.y,//Width of piece of bitmap
							position.x - offset.x, position.y - offset.y,//Where to draw it
							0, 0,//Scaling?
							0);	
}