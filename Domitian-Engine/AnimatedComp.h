#ifndef DAnimatedComp_H
#define DAnimatedComp_H

#include "Component.h"
#include "PositionComp.h"
#include "Radian.h"
#include <allegro5/bitmap_draw.h>
#include <allegro5/bitmap.h>
#include <vector>

class AnimatedComp : public Component
{
public:
	AnimatedComp(ALLEGRO_BITMAP* myBitmap,Vector2 myDimensions, PositionComp* myPosComp);
	void update(double);

	void setFrameX(double);
	void setFrameY(double);

	void setToVisible()
	{
		visible = true;
	};
	void setToInvisible()
	{
		visible = false;
	};

	void setAnimating(bool myTruth)
	{
		animating = myTruth;
	};

private:
	PositionComp* positionComp;

	bool visible;
	bool animating;

	ALLEGRO_BITMAP* bitmap;
	std::vector<std::vector<ALLEGRO_BITMAP*>> bitmap_2Dvector;

	double frame_interval;
	double current_time;

	Vector2 dimensions;
	Vector2 current_frame;
	Vector2 offset;
	
	Vector2 number_frames;

	void initialize() override
	{
		name = "Animated";
	};
};
#endif