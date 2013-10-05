#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

//allegro-5.0.10-monolith-md-debug.lib

#include "Domitian-Engine.h"

int main()
{
	//FPS
	double FPS=0;
	double total_frames = 0;
	double time_of_last_tick =0;
	double elapsed_time=0;
	double old_time=0;

	const double dt = 0.05;
	double accumulator = 0.0;

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

	//ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
	//ALLEGRO_BITMAP* generic_bitmap = al_load_bitmap("spaceship.png");

	boolean done = false;
	while(!done)
	{
		//FPS
		total_frames++;
		double total_seconds = al_get_time();//Time since the game began
		double seconds_since_last_tick = total_seconds - time_of_last_tick;
		time_of_last_tick = total_seconds;
		elapsed_time += seconds_since_last_tick;

		if ( seconds_since_last_tick > 0.25 )
		{
			seconds_since_last_tick = 0.25;	
		}
		accumulator+=seconds_since_last_tick;

		while ( accumulator >= dt )
		{

			accumulator -= dt;
			total_seconds += dt;
		}

		al_get_keyboard_state(&new_keyboard_state);
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			done = true;
		}


		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	//al_destroy_font(font24);
	//al_destroy_bitmap(generic_bitmap);
	al_destroy_display(display);
	return 0;
}