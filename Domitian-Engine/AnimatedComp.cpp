#include "AnimatedComp.h"

AnimatedComp::AnimatedComp(ALLEGRO_BITMAP* myBitmap,Vector2 myDimensions, Entity* myParent)
	:Component("Animated",myParent),bitmap(myBitmap),dimensions(myDimensions)
{
	positionComp = (PositionComp*) getComponent("Position");

	offset = Vector2 (dimensions.x/2,dimensions.y/2);
	
	current_frame = Vector2(0,0);
	number_frames = Vector2 (al_get_bitmap_width(bitmap)/dimensions.x, al_get_bitmap_height(bitmap)/dimensions.y);
	
	//Populating our bitmap array
	//[(int)number_frames.x*(int)number_frames.y];

	for (int x = 0; x < number_frames.x; ++x)
	{
		std::vector<ALLEGRO_BITMAP*> one_dim;
		bitmap_2Dvector.push_back(one_dim);
	}

	for (int y = 0; y < number_frames.y; ++y)
	{
		for (int x = 0; x < number_frames.x; ++x)
		{
			//int index = x *(int)number_frames.y + y;
			bitmap_2Dvector[x].push_back(al_create_sub_bitmap(	bitmap, x * dimensions.x, y * dimensions.y,		dimensions.x,dimensions.y));
		}
	}
	

	frame_interval=.1;
	
	current_time =0;
}

void AnimatedComp::setFrameX(float x)
{
	if(x>0&& x < number_frames.x+1)
	{
		current_frame.x = x;
	}
}

void AnimatedComp::setFrameY(float y)
{
	if(y>0&&y<number_frames.y+1)
	{
		current_frame.y = y;
	}
}

void AnimatedComp::update(float dt)
{
	if(current_time>frame_interval)
	{
		current_time = 0;

		current_frame.x++;

		if(current_frame.x>=number_frames.x)
			current_frame.x= 0;
	}

	current_time+=dt;

	al_draw_rotated_bitmap(	bitmap_2Dvector[current_frame.x][current_frame.y],
							offset.x,offset.y,
							positionComp->getPosition().x,-positionComp->getPosition().y,
							Radian::convertToGame(positionComp->getRotation()), 
							0);	
}