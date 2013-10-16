#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "Domitian-Engine.h"

#pragma region Preproccessor

#define PI 3.14159265
#define deg2rad( a ) a * (PI/180)

#pragma endregion

int main()
{
	//std::to_string(float (0));
#pragma region FPS

	double FPS=0;
	double total_frames=0;
	double previous_tick_timestamp =0;
	double elapsed_time=0;
	double old_time=0;

	const double dt = 0.05;
	const double doubledt = dt*5;
	double accumulator = 0.0;

#pragma endregion
	
#pragma region Allegro

	al_init(); //allegro-5.0.10-monolith-md-debug.lib
	
	//Anti Aliasing
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	
	//Creating screen
	int screen_width = 800;
	int screen_height = 600;
	ALLEGRO_DISPLAY* display = al_create_display(screen_width,screen_height);
	al_set_window_position(display,0,0);
	al_set_window_title(display, "Domitian Engine");

	//Initializing Addons
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE new_keyboard_state,old_keyboard_state;

#pragma endregion
	
#pragma region LoadContent
	
	ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
	ALLEGRO_BITMAP* player_bitmap = al_load_bitmap("fighter.png");
	ALLEGRO_BITMAP* animation_bitmap = al_load_bitmap("animation.png");

#pragma endregion 
	
#pragma region GameWorld

	std::vector<Entity*> entities;

	Entity player; 
	entities.push_back(&player);
	
	PositionComp player_position (Vector3 (100,100,10), -(PI/2), &player);
	player.addEntity(&player_position);

	SpriteComp player_sprite (player_bitmap, &player);
	player.addEntity(&player_sprite);

	PhysicsComp player_physics (100,al_get_bitmap_width(player_bitmap),&player);
	player.addEntity(&player_physics);

	player_physics.addForce(Force(-(PI/2), PI/2, 100000));

#pragma endregion
	
#pragma region GameLoop

	boolean done = false;
	while(!done)
	{
		#pragma region FPS

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

		#pragma endregion

		#pragma region Input

		al_get_keyboard_state(&new_keyboard_state);
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_ESCAPE))
		{
			done = true;
		}
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
		{
			//player_physics.addDisplacedForce(Force(Vector2(10,0),0.5,10));
			if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_W))
			{
				//player_position.setRotation(player_position.getRotation() + (deg2rad(10));
			}
		}

		old_keyboard_state = new_keyboard_state;

		#pragma endregion

		#pragma region Updating

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
		
		//Update the entities
		for(std::vector<Entity*>::size_type i = 0; i != entities.size(); i++) 
		{
			entities[i]->update(dt);
		}
		
        #pragma endregion

		#pragma region Drawing_GUI
		
		for(int y= 0 ; y<100; y++)
		{
			for(int x= 0 ; x<100; x++)
			{
				al_draw_pixel(x*200+1,y*200,al_map_rgb(	 200,200,200));
				al_draw_pixel(x*200-1,y*200,al_map_rgb(  200,200,200));
				al_draw_pixel(x*200,  y*200+1,al_map_rgb(200,200,200));
				al_draw_pixel(x*200,  y*200-1,al_map_rgb(200,200,200));
				al_draw_pixel(x*200,  y*200,al_map_rgb(  200,200,200));
			}
		}

		#pragma endregion
		
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