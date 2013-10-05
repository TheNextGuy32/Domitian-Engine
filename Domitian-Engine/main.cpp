#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>

//allegro-5.0.10-monolith-md-debug.lib

#include "Domitian-Engine.h"

int main()
{

#pragma region FPS

	double FPS=0;
	double total_frames=0;
	double previous_tick_timestamp =0;
	double elapsed_time=0;
	double old_time=0;

	const double dt = 0.05;
	double accumulator = 0.0;

#pragma endregion

#pragma region Allegro
	al_init();

	int screen_width = 800;
	int screen_height = 600;
	ALLEGRO_DISPLAY* display = al_create_display(screen_width,screen_height);
	al_set_window_position(display,0,0);
	al_set_window_title(display, "Domitian Engine");

	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE new_keyboard_state,old_keyboard_state;
#pragma endregion

#pragma region LoadContent
	ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
	ALLEGRO_BITMAP* player_bitmap = al_load_bitmap("player.png");

#pragma endregion 

#pragma region GameWorld

	Entity player;
	PositionComp player_position (Vector3 (10,10,10), 0, &player);
	player.addEntity(&player_position);

	SpriteComp player_sprite (player_bitmap, &player);
	player.addEntity(&player_sprite);

#pragma endregion

#pragma region GameLoop
	boolean done = false;
	while(!done)
	{
		//FPS
		total_frames++;
		double current_timestamp = al_get_time();
		double seconds_since_last_tick = current_timestamp - previous_tick_timestamp;
		previous_tick_timestamp = current_timestamp;
		elapsed_time += seconds_since_last_tick;
		if(elapsed_time>=1)
		{
			FPS = total_frames;
			elapsed_time--;
			total_frames = 0;	
		}

		accumulator+=seconds_since_last_tick;
		if ( seconds_since_last_tick > 0.25 )
		{
			seconds_since_last_tick = 0.25;	
		}
		
		//Do this before drawing
		while ( accumulator >= dt )
		{
			accumulator -= dt;
			current_timestamp += dt;
		}
		//player.update(dt);
		
		//INPUT
		al_get_keyboard_state(&new_keyboard_state);
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			done = true;
		}

		//Drawing FPS
		al_draw_text(font24, al_map_rgb(255,0,255),0,50,0, ("FPS: "+std::to_string(FPS)).c_str());

		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
#pragma endregion

#pragma region ReleaseContent
	al_destroy_font(font24);
	al_destroy_bitmap(player_bitmap);
	al_destroy_display(display);
#pragma endregion

	return 0;
}