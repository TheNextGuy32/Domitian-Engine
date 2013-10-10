#include "AnimatedComp.h"

AnimatedComp::AnimatedComp(ALLEGRO_BITMAP* myBitmap,Vector2 myDimensions, Entity* myParent)
	:Component("Animated",myParent),bitmap(myBitmap),dimensions(myDimensions)
{
	offset = Vector2 (dimensions.x/2,dimensions.y/2);
	frame = Vector2(0,0);
	frames = Vector2 (al_get_bitmap_width(bitmap)/dimensions.x,al_get_bitmap_height(bitmap)/dimensions.y);
	frame_interval=.2;
	current_time =0;
}

void AnimatedComp::setFrameX(float x)
{
	if(x>0&& x < frames.x+1)
	{
		frame.x = x;
	}
}

void AnimatedComp::setFrameY(float y)
{
	if(y>0&&y<frames.y+1)
	{
		frame.y = y;
	}
}

void AnimatedComp::update(float dt)
{
	if(current_time>frame_interval)
	{
		current_time = 0;
		frame.x++;
		if(frame.x>=frames.x)
			frame.x= 0;
	}
	current_time+=dt;


	PositionComp* positionComp = (PositionComp*) getComponent("Position");

	Vector3 position = positionComp->getPosition();

	al_draw_bitmap_region(	bitmap, 
							frame.x * dimensions.x, frame.y * dimensions.y,//Where to start within bitmap
							dimensions.x, dimensions.y,//Width of piece of bitmap
							position.x - offset.x, position.y - offset.y,//Where to draw it
							0);	
	

}