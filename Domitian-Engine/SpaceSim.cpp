#include "SpaceSim.h"

SpaceSim::SpaceSim()
{
	Initialize();
};
void SpaceSim::Initialize()
{
	done= false;
	FPS=0;
	total_frames=0;
	previous_tick_timestamp =0;
	elapsed_time=0;
	old_time=0;

	dt = .05;
	doubledt = dt*5;
	accumulator = 0.0;

	LoadContent();

	CreateWorld();

	Update();
	//Disconnect draw and update
};

void SpaceSim::LoadContent()
{
	LoadAllegro();

	font24 = al_load_font("arial.ttf", 24, 0);

	red_ball = al_load_bitmap("fighter.png");
	maroon_ball = al_load_bitmap("fightermaroon.png");

	animation_bitmap = al_load_bitmap("animation.png");

	astronaut_bitmap = al_load_bitmap("astronaut.png");
	dead_bitmap = al_load_bitmap("dead_astronaut.png");

	asteroid_bitmap = al_load_bitmap("asteroid.png");
	debris_bitmap = al_load_bitmap("debris.png");

	thrust_bitmap = al_load_bitmap("co2.png");

	iss_bitmap = al_load_bitmap("iss_piece.png");
	iss_plus_bitmap = al_load_bitmap("iss_plus.png");

	spaceship_bitmap= al_load_bitmap("space_ship.png");
	satellite_bitmap= al_load_bitmap("satellite.png");

	co2_bar_bitmap = al_load_bitmap("co2Canister.bmp");
	oxygen_bar_bitmap = al_load_bitmap("airCanister.bmp");

	co2_sample = al_load_sample("co2.wav");
	co2_sample_instance = al_create_sample_instance(co2_sample);
	al_set_sample_instance_playmode(co2_sample_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(co2_sample_instance,al_get_default_mixer());

	co2_back_sample = al_load_sample("co2.wav");
	co2_back_sample_instance = al_create_sample_instance(co2_back_sample);
	al_set_sample_instance_playmode(co2_back_sample_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(co2_back_sample_instance,al_get_default_mixer());

	co2_left_sample = al_load_sample("leftco2.wav");
	co2_left_sample_instance = al_create_sample_instance(co2_left_sample);
	al_set_sample_instance_playmode(co2_left_sample_instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(co2_left_sample_instance,al_get_default_mixer());

	co2_right_sample = al_load_sample("rightco2.wav");
	co2_right_sample_instance =al_create_sample_instance(co2_right_sample);
	al_set_sample_instance_playmode(co2_right_sample_instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(co2_right_sample_instance,al_get_default_mixer());
};
void SpaceSim::LoadAllegro()
{
	al_init(); //allegro-5.0.10-monolith-md-debug.lib

	//Anti Aliasing
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	//Creating screen
	screen_width = 1350;
	screen_height = 690;
	display = al_create_display(screen_width,screen_height);
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
};

void SpaceSim::CreateWorld()
{
	CreatePlayer();
	for(int p = 0 ; p <10; p++)
	{
		CreateAsteroid();

	}
	for(int p = 0 ; p < 0; p++)
	{
		CreateDebris();
	}
	CreateSpaceStation();
	CreateGUI();
};
void SpaceSim::CreatePlayer()
{
	Entity* player = new Entity();

	entities.push_back(player);
	physics_entities.push_back(player);

	player_position = new PositionComp (Vector3 (200,-200,10), 0, player);
	player->addComponent(player_position);

	player_sprite = new SpriteComp (astronaut_bitmap, player);
	player->addComponent(player_sprite);

	player_physics = new PhysicsComp (10,al_get_bitmap_width(astronaut_bitmap)/2,player);
	player->addComponent(player_physics);

	// Thrust
	thrust = new Entity();
	entities.push_back(thrust);

	thrust_position = new PositionComp (Vector3 (100,-100,10),0,thrust);
	thrust->addComponent(thrust_position);

	thrust_animated = new AnimatedComp (thrust_bitmap,Vector2(30,80),thrust);
	thrust->addComponent(thrust_animated);

	thrust_connected = new ConnectedComp (player_position->getRotation()-(PI),player_physics->getRadius(),thrust,player_position);
	thrust_connected->attach(player_position,true);
	thrust->addComponent(thrust_connected);

	// Back thrust
	thrust_back = new Entity();
	entities.push_back(thrust_back);

	thrust_back_position = new PositionComp (Vector3 (100,-100,10),PI,thrust);
	thrust_back->addComponent(thrust_back_position);

	thrust_back_animated = new AnimatedComp(thrust_bitmap,Vector2(30,80),thrust_back);
	thrust_back->addComponent(thrust_back_animated);

	thrust_back_connected = new ConnectedComp (player_position->getRotation(),player_physics->getRadius(),thrust_back,player_position);
	thrust_back_connected->attach(player_position,true);
	thrust_back->addComponent(thrust_back_connected);

	//Right Thrust
	thrust_right = new Entity();
	entities.push_back(thrust_right);

	thrust_right_position = new PositionComp (Vector3 (100,-100,10),0,thrust_right);
	thrust_right->addComponent(thrust_right_position);

	thrust_right_animated = new AnimatedComp (thrust_bitmap,Vector2(30,80),thrust_right);
	thrust_right->addComponent(thrust_right_animated);

	thrust_right_connected = new ConnectedComp (player_position->getRotation()-(PI/2.0),player_physics->getRadius(),thrust_right,player_position);
	thrust_right_connected->attach(player_position,true);
	thrust_right->addComponent(thrust_right_connected);

	//Left Thrust
	thrust_left = new Entity();
	entities.push_back(thrust_left);

	thrust_left_position = new PositionComp (Vector3 (100,-100,10),0,thrust_left);
	thrust_left->addComponent(thrust_left_position);

	thrust_left_animated = new AnimatedComp (thrust_bitmap,Vector2(30,80),thrust_left);
	thrust_left->addComponent(thrust_left_animated);

	thrust_left_connected = new ConnectedComp (player_position->getRotation()+(PI/2.0),player_physics->getRadius(),thrust_left,player_position);
	thrust_left_connected->attach(player_position,true);
	thrust_left->addComponent(thrust_left_connected);
};
void SpaceSim::CreateAsteroid()
{
	Entity* ball = new Entity(); 
	entities.push_back(ball);
	physics_entities.push_back(ball);

	double x = std::rand()%(screen_width-100)+50;
	double y = -(std::rand()%(screen_height-100)+50);

	ball->addComponent(new PositionComp(Vector3 (x,y,10), 0, ball));		
	ball->addComponent(new SpriteComp (asteroid_bitmap, ball));
	ball->addComponent(new PhysicsComp (2000,al_get_bitmap_width(asteroid_bitmap)/2,ball));
};
void SpaceSim::CreateDebris()
{
	Entity* debris = new Entity(); 
	entities.push_back(debris);
	physics_entities.push_back(debris);

	double x = std::rand()%(screen_width-1300)+300;
	double y = -(std::rand()%(screen_height-600)+100);

	debris->addComponent(new PositionComp(Vector3 (x,y,10), 0, debris));		
	debris->addComponent(new SpriteComp (debris_bitmap, debris));
	debris->addComponent(new PhysicsComp (0.1,al_get_bitmap_width(debris_bitmap)/2,debris));
};
void SpaceSim::CreateSpaceStation()
{
	spaceship = new Entity();
	entities.push_back(spaceship);
	physics_entities.push_back(spaceship);
	spaceship->addComponent(new PositionComp(Vector3 (250,-500,10), -PI/4, spaceship));		
	spaceship->addComponent(new SpriteComp (spaceship_bitmap, spaceship));
	PhysicsComp* spaceship_phys = new PhysicsComp (1000000,al_get_bitmap_height(spaceship_bitmap)/2,spaceship);
	//spaceship_phys->addForce(Force(PI,-PI/2,5000000));
	spaceship->addComponent(spaceship_phys);

	satellite = new Entity();
	entities.push_back(satellite);
	physics_entities.push_back(satellite);
	satellite->addComponent(new PositionComp(Vector3 (1000,-250,10), -PI/2, satellite));		
	satellite->addComponent(new SpriteComp (satellite_bitmap, satellite));
	PhysicsComp* phys = new PhysicsComp (1000000,al_get_bitmap_height(satellite_bitmap)/2,satellite);
	//phys->addForce(Force(0,PI/2,5000000));
	satellite->addComponent(phys);

	/*iss_piece_north = new Entity();
	entities.push_back(iss_piece_north);
	physics_entities.push_back(iss_piece_north);
	iss_piece_north->addComponent(new PositionComp(Vector3 (0,0,10), 0, iss_piece_north));		
	iss_piece_north->addComponent(new SpriteComp (iss_bitmap, iss_piece_north));
	iss_piece_north->addComponent(new PhysicsComp (1000000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_north));
	ConnectedComp* iss_north_attached = new ConnectedComp (PI/2,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_north,&player_position);
	iss_north_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_north->addComponent(iss_north_attached);

	iss_piece_east = new Entity();
	entities.push_back(iss_piece_east);
	physics_entities.push_back(iss_piece_east);
	iss_piece_east->addComponent(new PositionComp(Vector3 (0,0,10), PI/2, iss_piece_east));		
	iss_piece_east->addComponent(new SpriteComp (iss_bitmap, iss_piece_east));
	iss_piece_east->addComponent(new PhysicsComp (1000000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_east));
	ConnectedComp* iss_east_attached = new ConnectedComp (0,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_east,&player_position);
	iss_east_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_east->addComponent(iss_east_attached);

	iss_piece_south = new Entity();
	entities.push_back(iss_piece_south);
	physics_entities.push_back(iss_piece_south);
	iss_piece_south->addComponent(new PositionComp(Vector3 (0,0,10), 0, iss_piece_south));		
	iss_piece_south->addComponent(new SpriteComp (iss_bitmap, iss_piece_south));
	iss_piece_south->addComponent(new PhysicsComp (1000000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_south));
	ConnectedComp* iss_south_attached = new ConnectedComp (-PI/2,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_south,&player_position);
	iss_south_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_south->addComponent(iss_south_attached);

	iss_piece_west = new Entity();
	entities.push_back(iss_piece_west);
	physics_entities.push_back(iss_piece_west);
	iss_piece_west->addComponent(new PositionComp(Vector3 (0,0,10), PI/2, iss_piece_west));		
	iss_piece_west->addComponent(new SpriteComp (iss_bitmap, iss_piece_west));
	iss_piece_west->addComponent(new PhysicsComp (1000000,al_get_bitmap_height(iss_bitmap)/2,iss_piece_west));
	ConnectedComp* iss_west_attached = new ConnectedComp (PI,al_get_bitmap_width(iss_bitmap)/2 + al_get_bitmap_height(iss_plus_bitmap)/2,iss_piece_west,&player_position);
	iss_west_attached->attach((PositionComp*)iss_plus->getComponent("Position"),true);
	iss_piece_west->addComponent(iss_west_attached);*/
};
void SpaceSim::CreateGUI()
{
	double space_between_bars_x = 1;
	double space_between_bars_y = 5;

	double oxygen_position_x = 275;
	double oxygen_position_y = -650;

	for(int p = 0 ; p < 100 ; p++)
	{
		Entity* oxygen_bar = new Entity();
		entities.push_back(oxygen_bar);
		oxygen_bars[p] = oxygen_bar;

		//
		PositionComp* oxy_pos = new PositionComp(Vector3(oxygen_position_x+(p*(space_between_bars_x+al_get_bitmap_width(oxygen_bar_bitmap))),oxygen_position_y,10),oxygen_bar);
		oxy_pos->setRotation(PI/2);
		oxygen_bar->addComponent(oxy_pos);
		oxygen_bar->addComponent(new SpriteComp(oxygen_bar_bitmap,oxygen_bar));

		Entity* co2_bar = new Entity();
		entities.push_back(co2_bar);
		co2_bars[p] = co2_bar;

		PositionComp* co2_pos = new PositionComp(Vector3(oxygen_position_x+(p*(space_between_bars_x+al_get_bitmap_width(oxygen_bar_bitmap))),oxygen_position_y-al_get_bitmap_height(oxygen_bar_bitmap)-space_between_bars_y,10),
			co2_bar);
		co2_pos->setRotation(PI/2);
		co2_bar->addComponent(co2_pos);
			
		co2_bar->addComponent(new SpriteComp(co2_bar_bitmap,co2_bar));
	}
};

void SpaceSim::UnloadContent()
{
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
	al_destroy_sample(co2_back_sample);
	al_destroy_sample_instance(co2_left_sample_instance);
	al_destroy_sample_instance(co2_right_sample_instance);
	al_destroy_sample_instance(co2_sample_instance);
	al_destroy_sample_instance(co2_back_sample_instance);

	al_destroy_display(display);

	for(int p = 0 ; p < entities.size(); p++)
	{
		delete(entities[p]);
	}
};

void SpaceSim::Update()
{
	thrust_animated->setToInvisible();
	thrust_back_animated->setToInvisible();
	thrust_right_animated->setToInvisible();
	thrust_left_animated->setToInvisible();
	while(!done)
	{
		double current_timestamp = al_get_time();
		double seconds_since_last_tick = current_timestamp - previous_tick_timestamp;
		if(seconds_since_last_tick > .25)
		{
			seconds_since_last_tick = 0.25;

		}
		previous_tick_timestamp = current_timestamp;

		accumulator+=seconds_since_last_tick;

		//Do this before drawing
		while ( accumulator >= dt )
		{
			TakeInput();
			for(std::vector<Entity*>::size_type i = 0; i != entities.size(); i++) 
			{
				entities[i]->update(dt);
			}

			//CHECKING COLLISION and wrap 
			for(int i = 0; i != physics_entities.size(); i++) 
			{
				PositionComp* pos = (PositionComp*) physics_entities[i]->getComponent("Position");
				SpriteComp* spr = (SpriteComp*) physics_entities[i]->getComponent("Sprite");
				PhysicsComp* phys = (PhysicsComp*) physics_entities[i]->getComponent("Physics");

				//Collisions
				for(int q = 0; q != physics_entities.size(); q++) 
				{
					if(i!=q)
					{
						PhysicsComp* collider = (PhysicsComp*) physics_entities[q]->getComponent("Physics");
						PhysicsComp::checkCollision(phys,collider);
					}
				}
				//Boundaries
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
				//Bottom
				if( (pos->getPosition().y + al_get_bitmap_height (spr->getBitmap())/2 ) < -screen_height)
				{
					pos->setPositionY(pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 + screen_height);
				}
			}
			accumulator -= dt;
		}

		/* Gets rid of displeasing effect
		const double alpha = accumulator / dt;
		State state = currentState*alpha + previousState * ( 1.0 - alpha );*/

		Draw();
	}
};

void SpaceSim::TakeInput()
{
	al_get_keyboard_state(&new_keyboard_state);

	//ESCAPE
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_ESCAPE))
	{
		done = true;
	}

	//Q
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_Q))
	{
		if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_Q))
		{
			player_sprite->setBitmap(dead_bitmap);
		}
	}

	//W
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
	{
		thrust_animated->setToVisible();
		player_physics->addForce(Force(player_position->getRotation()+PI,player_position->getRotation(),1000));
		if(!al_get_sample_instance_playing(co2_sample_instance))
		{
			al_play_sample_instance(co2_sample_instance);
		}		
	}
	else
	{
		thrust_animated->setToInvisible();
		al_stop_sample_instance(co2_sample_instance);
	}

	//S
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_S))
	{
		thrust_back_animated->setToVisible();
		player_physics->addForce(Force(player_position->getRotation(),player_position->getRotation()+PI,1000));

		if(!al_get_sample_instance_playing(co2_sample_instance))
		{
			al_play_sample_instance(co2_back_sample_instance);
		}		
	}
	else
	{
		thrust_back_animated->setToInvisible();
		al_stop_sample_instance(co2_back_sample_instance);
	}

	//D
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_D))
	{
		thrust_right_animated->setToVisible();
		player_physics->addForce(Force(player_position->getRotation()-(PI/2.0),player_position->getRotation(),1000));
		if(!al_get_sample_instance_playing(co2_right_sample_instance))
		{
			al_play_sample_instance(co2_right_sample_instance);
		}		
	}
	else
	{
		thrust_right_animated->setToInvisible();
		al_stop_sample_instance(co2_right_sample_instance);
	}

	//A
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_A))
	{
		thrust_left_animated->setToVisible();
		player_physics->addForce(Force(player_position->getRotation()+(PI/2.0),player_position->getRotation(),1000));
		if(!al_get_sample_instance_playing(co2_sample_instance))
		{
			al_play_sample_instance(co2_left_sample_instance);
		}		
	}
	else
	{
		thrust_left_animated->setToInvisible();
		al_stop_sample_instance(co2_left_sample_instance);
	}


	old_keyboard_state = new_keyboard_state;
}

void SpaceSim::Draw()
{
	//DrawScreenNodes();
	for(std::vector<Entity*>::size_type i = 0; i != entities.size(); i++) 
	{
		entities[i]->draw(dt);
	}

	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
}

void SpaceSim::DrawScreenNodes()
{
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
};