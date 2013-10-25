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
	AnimatedComp(ALLEGRO_BITMAP*,Vector2,Entity*);
	void update(float);

	void setFrameX(float);
	void setFrameY(float);

	void setAnimating(bool myTruth)
	{
		animating = myTruth;
	};

private:
	PositionComp* positionComp;

	bool animating;

	ALLEGRO_BITMAP* bitmap;
	std::vector<std::vector<ALLEGRO_BITMAP*>> bitmap_2Dvector;

	float frame_interval;
	float current_time;

	Vector2 dimensions;
	Vector2 current_frame;
	Vector2 offset;
	
	Vector2 number_frames;


};
#endif