#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
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
	int screen_width = 1350;
	int screen_height = 690;
	ALLEGRO_DISPLAY* display = al_create_display(screen_width,screen_height);
	al_set_window_position(display,0,0);
	al_set_window_title(display, "Domitian Engine");

	//Initializing Addons
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(10);

	ALLEGRO_KEYBOARD_STATE new_keyboard_state,old_keyboard_state;

#pragma endregion

#pragma region LoadContent

	ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);

	ALLEGRO_BITMAP* red_ball = al_load_bitmap("fighter.png");
	ALLEGRO_BITMAP* maroon_ball = al_load_bitmap("fightermaroon.png");

	ALLEGRO_BITMAP* animation_bitmap = al_load_bitmap("animation.png");

	ALLEGRO_BITMAP* astronaut_bitmap = al_load_bitmap("astronaut.png");
	ALLEGRO_BITMAP* dead_bitmap = al_load_bitmap("dead_astronaut.png");

	ALLEGRO_BITMAP* asteroid_bitmap = al_load_bitmap("asteroid.png");

	ALLEGRO_BITMAP* thrust_bitmap = al_load_bitmap("co2.png");

	ALLEGRO_BITMAP* iss_bitmap = al_load_bitmap("iss_piece.png");
	ALLEGRO_BITMAP* iss_plus_bitmap = al_load_bitmap("iss_plus.png");

	ALLEGRO_SAMPLE* co2_sample = al_load_sample("co2.wav");
	ALLEGRO_SAMPLE_INSTANCE* co2_sample_instance = al_create_sample_instance(co2_sample);
	al_set_sample_instance_playmode(co2_sample_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(co2_sample_instance,al_get_default_mixer());

	ALLEGRO_SAMPLE* co2_left_sample = al_load_sample("leftco2.wav");
	ALLEGRO_SAMPLE_INSTANCE* co2_left_sample_instance = al_create_sample_instance(co2_left_sample);
	al_set_sample_instance_playmode(co2_left_sample_instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(co2_left_sample_instance,al_get_default_mixer());

	ALLEGRO_SAMPLE* co2_right_sample = al_load_sample("rightco2.wav");
	ALLEGRO_SAMPLE_INSTANCE* co2_right_sample_instance =al_create_sample_instance(co2_right_sample);
	al_set_sample_instance_playmode(co2_right_sample_instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(co2_right_sample_instance,al_get_default_mixer());

#pragma endregion 

#pragma region GameWorld

	std::vector<Entity*> entities;
	std::vector<Entity*> physics_entities;

	

	//Player
	Entity* player = new Entity(); 
	entities.push_back(player);
	physics_entities.push_back(player);

	PositionComp player_position (Vector3 (200,-200,10), 0, player);
	player->addComponent(&player_position);

	SpriteComp player_sprite (astronaut_bitmap, player);
	player->addComponent(&player_sprite);

	PhysicsComp player_physics (20,al_get_bitmap_width(astronaut_bitmap)/2,player);
	player->addComponent(&player_physics);

	// Thrust
	Entity* thrust = new Entity();
	entities.push_back(thrust);

	PositionComp thrust_position (Vector3 (100,-100,10),PI,thrust);
	thrust->addComponent(&thrust_position);

	AnimatedComp thrust_animated (thrust_bitmap,Vector2(30,80),thrust);
	thrust->addComponent(&thrust_animated);

	ConnectedComp thrust_connected (player_position.getRotation()-(3.1459),player_physics.getRadius(),thrust);
	thrust_connected.attach(&player_position,true);
	thrust->addComponent(&thrust_connected);

	//Right Thrust
	Entity* thrust_right = new Entity();
	entities.push_back(thrust_right);

	PositionComp thrust_right_position (Vector3 (100,-100,10),PI,thrust_right);
	thrust_right->addComponent(&thrust_right_position);

	AnimatedComp thrust_right_animated (thrust_bitmap,Vector2(30,80),thrust_right);
	thrust_right->addComponent(&thrust_right_animated);

	ConnectedComp thrust_right_connected (player_position.getRotation()-(3.1459/2.0),player_physics.getRadius(),thrust_right);
	thrust_right_connected.attach(&player_position,true);
	thrust_right->addComponent(&thrust_right_connected);

	//Left Thrust
	Entity* thrust_left = new Entity();
	entities.push_back(thrust_left);

	PositionComp thrust_left_position (Vector3 (100,-100,10),PI,thrust_left);
	thrust_left->addComponent(&thrust_left_position);

	AnimatedComp thrust_left_animated (thrust_bitmap,Vector2(30,80),thrust_left);
	thrust_left->addComponent(&thrust_left_animated);

	ConnectedComp thrust_left_connected (player_position.getRotation()+(3.1459/2.0),player_physics.getRadius(),thrust_left);
	thrust_left_connected.attach(&player_position,true);
	thrust_left->addComponent(&thrust_left_connected);

	Entity *ball;
	for(int e = 0 ; e < 15 ; e++)
	{
		ball = new Entity(); 
		entities.push_back(ball);
		physics_entities.push_back(ball);

		float x = std::rand()%(screen_width-100)+50;
		float y = -(std::rand()%(screen_height-100)+50);

		ball->addComponent(new PositionComp(Vector3 (x,y,10), 0, ball));		
		ball->addComponent(new SpriteComp (asteroid_bitmap, ball));
		ball->addComponent(new PhysicsComp (20,al_get_bitmap_width(asteroid_bitmap)/2,ball));
	}

	Entity* iss_plus = new Entity();
	entities.push_back(iss_plus);
	physics_entities.push_back(iss_plus);
	iss_plus->addComponent(new PositionComp(Vector3 (500,-500,10), 0, iss_plus));		
	iss_plus->addComponent(new SpriteComp (iss_plus_bitmap, iss_plus));
	iss_plus->addComponent(new PhysicsComp (10000,al_get_bitmap_height(iss_plus_bitmap)/2,iss_plus));

	Entity* iss_piece_north = new Entity();
	entities.push_back(iss_piece_north);
	physics_entities.push_back(iss_piece_north);
	iss_piece_north->addComponent(new PositionComp(Vector3 (0,0,10), 0, iss_piece_north));		
	iss_piece_north->addComponent(new SpriteComp (iss_bitmap, iss_piece_north));
	iss_piece_north->addComponent(new PhysicsComp (10000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_north));
	ConnectedComp* iss_north_attached = new ConnectedComp (PI/2,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_north);
	iss_north_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_north->addComponent(iss_north_attached);

	Entity* iss_piece_east = new Entity();
	entities.push_back(iss_piece_east);
	physics_entities.push_back(iss_piece_east);
	iss_piece_east->addComponent(new PositionComp(Vector3 (0,0,10), PI/2, iss_piece_east));		
	iss_piece_east->addComponent(new SpriteComp (iss_bitmap, iss_piece_east));
	iss_piece_east->addComponent(new PhysicsComp (10000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_east));
	ConnectedComp* iss_east_attached = new ConnectedComp (0,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_east);
	iss_east_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_east->addComponent(iss_east_attached);

	Entity* iss_piece_south = new Entity();
	entities.push_back(iss_piece_south);
	physics_entities.push_back(iss_piece_south);
	iss_piece_south->addComponent(new PositionComp(Vector3 (0,0,10), 0, iss_piece_south));		
	iss_piece_south->addComponent(new SpriteComp (iss_bitmap, iss_piece_south));
	iss_piece_south->addComponent(new PhysicsComp (10000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_south));
	ConnectedComp* iss_south_attached = new ConnectedComp (-PI/2,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_south);
	iss_south_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_south->addComponent(iss_south_attached);

	Entity* iss_piece_west = new Entity();
	entities.push_back(iss_piece_west);
	physics_entities.push_back(iss_piece_west);
	iss_piece_west->addComponent(new PositionComp(Vector3 (0,0,10), PI/2, iss_piece_west));		
	iss_piece_west->addComponent(new SpriteComp (iss_bitmap, iss_piece_west));
	iss_piece_west->addComponent(new PhysicsComp (10000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_west));
	ConnectedComp* iss_west_attached = new ConnectedComp (PI,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_west);
	iss_west_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_west->addComponent(iss_west_attached);


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
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_Q))
		{
			if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_Q))
			{
				player_sprite.setBitmap(dead_bitmap);
			}
			
		}

		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
		{
			player_physics.addForce(Force(player_position.getRotation()+3.1459,player_position.getRotation(),1000));
			if(!al_get_sample_instance_playing(co2_sample_instance))
			{
				al_play_sample_instance(co2_sample_instance);
			}		
		}
		else
		{
			al_stop_sample_instance(co2_sample_instance);
		}

		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_S))
		{
			player_physics.addForce(Force(player_position.getRotation(),player_position.getRotation()+3.1459,1000));
		}
			/*if(!al_get_sample_instance_playing(co2_sample_instance))
			{
				al_play_sample_instance(co2_sample_instance);
			}		
		}
		else
		{
			al_stop_sample_instance(co2_sample_instance);
		}*/
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_D))
		{
			player_physics.addForce(Force(player_position.getRotation()-(3.1459/2.0),player_position.getRotation(),1000));
			if(!al_get_sample_instance_playing(co2_right_sample_instance))
			{
				al_play_sample_instance(co2_right_sample_instance);
			}		
		}
		else
		{
			al_stop_sample_instance(co2_right_sample_instance);
		}
		if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_A))
		{
			player_physics.addForce(Force(player_position.getRotation()+(3.1459/2.0),player_position.getRotation(),1000));
			if(!al_get_sample_instance_playing(co2_sample_instance))
			{
				al_play_sample_instance(co2_left_sample_instance);
			}		
		}
		else
		{
			al_stop_sample_instance(co2_left_sample_instance);
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

		for(int i = 0; i != physics_entities.size(); i++) 
		{
			PositionComp* pos = (PositionComp*) physics_entities[i]->getComponent("Position");
			SpriteComp* spr = (SpriteComp*) physics_entities[i]->getComponent("Sprite");

			//Right
			if( (pos->getPosition().x - al_get_bitmap_width (spr->getBitmap())/2 ) > screen_width)
			{
				pos->setPositionX(pos->getPosition().x - al_get_bitmap_width (spr->getBitmap())/2 - screen_width);
			}
			//Left
			if( (pos->getPosition().x + al_get_bitmap_width (spr->getBitmap())/2 ) < 0)
			{
				pos->setPositionX(pos->getPosition().x + al_get_bitmap_width (spr->getBitmap())/2 + screen_width);
			}
			//Top
			if( (pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 ) > 0)
			{
				pos->setPositionY(pos->getPosition().y + al_get_bitmap_height(spr->getBitmap())/2 - screen_height);
			}
			//Bpttom
			if( (pos->getPosition().y + al_get_bitmap_height (spr->getBitmap())/2 ) < -screen_height)
			{
				pos->setPositionY(pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 + screen_height);
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
	al_destroy_bitmap( iss_bitmap );

	al_destroy_sample(co2_left_sample);
	al_destroy_sample(co2_right_sample);
	al_destroy_sample(co2_sample);
	al_destroy_sample_instance(co2_left_sample_instance);
	al_destroy_sample_instance(co2_right_sample_instance);
	al_destroy_sample_instance(co2_sample_instance);

	al_destroy_display(display);


	for(int p = 0 ; p < entities.size(); p++)
	{
		delete(entities[p]);
	}

#pragma endregion

	return 0;
}