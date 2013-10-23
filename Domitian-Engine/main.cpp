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
	std::srand( time(NULL) );
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

	ALLEGRO_BITMAP* red_ball = al_load_bitmap("fighter.png");
	ALLEGRO_BITMAP* maroon_ball = al_load_bitmap("fightermaroon.png");

	ALLEGRO_BITMAP* animation_bitmap = al_load_bitmap("animation.png");

	ALLEGRO_BITMAP* astronaut_bitmap = al_load_bitmap("astronaut.png");

	ALLEGRO_BITMAP* asteroid_bitmap = al_load_bitmap("asteroid.png");

#pragma endregion 

#pragma region GameWorld

	std::vector<Entity*> entities;
	std::vector<Entity*> physics_entities;

	//Player
	Entity* player = new Entity(); 
	entities.push_back(player);
	physics_entities.push_back(player);

	PositionComp player_position (Vector3 (200,-200,10), 0, player);
	player->addEntity(&player_position);

	SpriteComp player_sprite (astronaut_bitmap, player);
	player->addEntity(&player_sprite);

	PhysicsComp player_physics (10,al_get_bitmap_width(astronaut_bitmap)/2,player);
	player->addEntity(&player_physics);

	//Collider
	Entity* collider  = new Entity(); 
	//entities.push_back(collider);
	//physics_entities.push_back(collider);

	PositionComp collider_position (Vector3 (200,-400,10), 0, collider);
	collider->addEntity(&collider_position);

	SpriteComp collider_sprite (maroon_ball, collider);
	collider->addEntity(&collider_sprite);

	PhysicsComp collider_physics (120,al_get_bitmap_width(red_ball)/2,collider);
	collider->addEntity(&collider_physics);

	collider_physics.addForce(Force(-(PI/2),(PI/2) , 100000));

	Entity *ball;
	for(int e = 0 ; e < 3 ; e++)
	{
		ball = new Entity(); 
		entities.push_back(ball);
		physics_entities.push_back(ball);

		float x = std::rand()%700+50;
		float y = -(std::rand()%500+50);

		ball->addEntity(new PositionComp(Vector3 (x,y,10), 0, ball));		
		ball->addEntity(new SpriteComp (asteroid_bitmap, ball));
		ball->addEntity(new PhysicsComp (50,al_get_bitmap_width(asteroid_bitmap)/2,ball));
	}

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
		/*if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
		{
		player_position.setRotation(player_position.getRotation()+0.01);
		}*/

		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
		{
			player_physics.addForce(Force(player_position.getRotation()+3.1459,player_position.getRotation(),1000));
		}

		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_S))
		{
			player_physics.addForce(Force(player_position.getRotation(),player_position.getRotation()+3.1459,1000));
		}

		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_D))
		{
			player_physics.addForce(Force(player_position.getRotation()-(3.1459/2.0),player_position.getRotation(),100));
		}
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_A))
		{
			player_physics.addForce(Force(player_position.getRotation()+(3.1459/2.0),player_position.getRotation(),100));
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

		//CHECKING COLLISION
		for(int i = 0; i != physics_entities.size(); i++) 
		{
			PhysicsComp* phys = (PhysicsComp*) physics_entities[i]->getComponent("Physics");

			for(int q = 0; q != physics_entities.size(); q++) 
			{
				if(i!=q)
				{
					PhysicsComp* collider = (PhysicsComp*) physics_entities[q]->getComponent("Physics");
					PhysicsComp::checkCollision(phys,collider);
				}
			}
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
	al_destroy_bitmap(red_ball);
	al_destroy_bitmap(animation_bitmap);
	al_destroy_bitmap(maroon_ball);
	al_destroy_bitmap(astronaut_bitmap);
	al_destroy_bitmap(asteroid_bitmap );
	al_destroy_display(display);


	for(int p = 0 ; p < entities.size(); p++)
	{
		delete(entities[p]);
	}

#pragma endregion

	return 0;
}