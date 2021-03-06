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
};

void SpaceSim::LoadContent()
{
	LoadAllegro();

	font24 = al_load_font("arial.ttf", 24, 0);

	/*red_ball = al_load_bitmap("fighter.png");
	maroon_ball = al_load_bitmap("fightermaroon.png");

	astronaut_bitmap = al_load_bitmap("astronaut.png");
	dead_bitmap = al_load_bitmap("dead_astronaut.png");*/

	asteroid_bitmap = al_load_bitmap("asteroid.png");
	debris_bitmap = al_load_bitmap("debris0.png");

	thrust_bitmap = al_load_bitmap("thruster_fire.png");

	/*iss_bitmap = al_load_bitmap("iss_piece.png");
	iss_plus_bitmap = al_load_bitmap("iss_plus.png");*/

	spaceship_bitmap= al_load_bitmap("spaceship.png");
	turret_bitmap = al_load_bitmap("turret.png");
	bullet_bitmap = al_load_bitmap("debris.png");
	tether_bitmap = al_load_bitmap("tether.png");

	/*co2_bar_bitmap = al_load_bitmap("co2Canister.bmp");
	oxygen_bar_bitmap = al_load_bitmap("airCanister.bmp");
	gui_bar_bitmap = al_load_bitmap("guiBar.bmp");

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
	al_attach_sample_instance_to_mixer(co2_right_sample_instance,al_get_default_mixer());*/
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
	////CreatePlayer();
	for(int p = 0 ; p <15; p++)
	{
		//CreateAsteroid();

	}
	for(int p = 0 ; p < 10; p++)
	{
		CreateDebris();
	}

	spaceship = CreateSpaceship(300,-450);
};
Combiner* SpaceSim::CreateSpaceship(double x, double y)
{
	Combiner* spaceship_combiner = new Combiner();

	//BODY
	Entity* spaceship = new Entity();
	entities.push_back(spaceship);
	physics_entities.push_back(spaceship);
	spaceship_combiner->addEntity("body",spaceship);

	PositionComp* spaceshipPos = new PositionComp(Vector3(x,y,15),0);
	spaceship->addComponent(spaceshipPos);
	spaceship->addComponent(new SpriteComp(spaceship_bitmap,spaceshipPos));
	spaceship->addComponent(new SpaceshipComp(30.0));
	PhysicsComp* spaceship_Phys = new PhysicsComp(100,al_get_bitmap_width(spaceship_bitmap)/2,0.2,spaceshipPos);
	spaceship->addComponent(spaceship_Phys);

	Entity* matcher = new Entity();
	entities.push_back(matcher);
	physics_entities.push_back(matcher);

	PositionComp* matcherPos = new PositionComp(Vector3(x+300,y+200,15),0);
	matcher->addComponent(matcherPos);
	matcher->addComponent(new SpriteComp(spaceship_bitmap,matcherPos));
	
	PhysicsComp* matcher_Phys = new PhysicsComp(100000000000,al_get_bitmap_width(spaceship_bitmap)/2,0.2,matcherPos);
	matcher->addComponent(matcher_Phys);

	//TURRETS
	Entity* turret_north = new Entity();
	entities.push_back(turret_north);
	spaceship_combiner->addEntity("turret_north",turret_north);

	PositionComp* n_pos = new PositionComp(Vector3(x,y,16),0);
	turret_north->addComponent(n_pos);
	turret_north->addComponent(new SpriteComp(turret_bitmap,n_pos));
	ConnectedComp* turret_north_connected = new ConnectedComp(0,al_get_bitmap_width(spaceship_bitmap)/2, spaceshipPos,n_pos);
	turret_north_connected->attach(spaceshipPos,true);
	turret_north->addComponent(turret_north_connected);
	turret_north->addComponent(new TurretComp(0.001,5,5,0.05));

	/*Entity* turret_east = new Entity();
	entities.push_back(turret_east);
	spaceship_combiner->addEntity("turret_east",turret_east);

	PositionComp* e_pos = new PositionComp(Vector3(x,y,16),-PI/2);
	turret_east->addComponent(e_pos);
	turret_east->addComponent(new SpriteComp(turret_bitmap,e_pos));
	ConnectedComp* turret_east_connected = new ConnectedComp(-PI/2,al_get_bitmap_width(spaceship_bitmap)/2, spaceshipPos,e_pos);
	turret_east_connected->attach(spaceshipPos,true);
	turret_east->addComponent(turret_east_connected);
	turret_east->addComponent(new TurretComp(10,500000,5,0.05));

	Entity* turret_west = new Entity();
	entities.push_back(turret_west);
	spaceship_combiner->addEntity("turret_west",turret_west);

	PositionComp* w_pos = new PositionComp(Vector3(x,y,16),PI/2);
	turret_west->addComponent(w_pos);
	turret_west->addComponent(new SpriteComp(turret_bitmap,w_pos));
	ConnectedComp* turret_west_connected = new ConnectedComp(PI/2,al_get_bitmap_width(spaceship_bitmap)/2, spaceshipPos,w_pos);
	turret_west_connected->attach(spaceshipPos,true);
	turret_west->addComponent(turret_west_connected);
	turret_west->addComponent(new TurretComp(10,500,5,0.05));
	*/
	//Thrusters!
	Entity* main_thruster = new Entity();
	entities.push_back(main_thruster);
	spaceship_combiner->addEntity("thruster_main",main_thruster);

	PositionComp* m_t_pos = new PositionComp(Vector3(0,0,16));
	main_thruster->addComponent(m_t_pos);
	main_thruster->addComponent(new AnimatedComp(thrust_bitmap,Vector2(30,80),m_t_pos));
	ConnectedComp* main_thruster_connected = new ConnectedComp(PI,al_get_bitmap_width(spaceship_bitmap)/2,spaceshipPos,m_t_pos);
	main_thruster_connected->attach(spaceshipPos,true);
	main_thruster->addComponent(main_thruster_connected);
	main_thruster->addComponent(new ThrusterComp(10000));

	Entity* west_thruster = new Entity();
	entities.push_back(west_thruster);
	spaceship_combiner->addEntity("thruster_west",west_thruster);

	PositionComp* w_t_pos = new PositionComp(Vector3(0,0,16),0);
	west_thruster->addComponent(w_t_pos);
	west_thruster->addComponent(new AnimatedComp(thrust_bitmap,Vector2(30,80),w_t_pos));
	ConnectedComp* west_thruster_connected = new ConnectedComp(PI/2,al_get_bitmap_width(spaceship_bitmap)/2,spaceshipPos,w_t_pos);
	west_thruster_connected->attach(spaceshipPos,true);
	west_thruster->addComponent(west_thruster_connected);
	west_thruster->addComponent(new ThrusterComp(1000));

	Entity* east_thruster = new Entity();
	entities.push_back(east_thruster);
	spaceship_combiner->addEntity("thruster_east",east_thruster);

	PositionComp* e_t_pos = new PositionComp(Vector3(0,0,16),0);
	east_thruster->addComponent(e_t_pos);
	east_thruster->addComponent(new AnimatedComp(thrust_bitmap,Vector2(30,80),e_t_pos));
	ConnectedComp* east_thruster_connected = new ConnectedComp(-PI/2,al_get_bitmap_width(spaceship_bitmap)/2,spaceshipPos,e_t_pos);
	east_thruster_connected->attach(spaceshipPos,true);
	east_thruster->addComponent(east_thruster_connected);
	east_thruster->addComponent(new ThrusterComp(1000));

	//Entity* spaceship_visual_tether = new Entity();
	//entities.push_back(spaceship_visual_tether);
	//PositionComp* spaceship_visual_tether_pos = new PositionComp(Vector3(0,0,16));
	//spaceship_visual_tether->addComponent(spaceship_visual_tether_pos);
	//spaceship_visual_tether->addComponent(new SpriteComp(tether_bitmap,spaceship_visual_tether_pos));
	//ConnectedComp* spaceship_visual_connect = new ConnectedComp(PI,30,spaceshipPos,spaceship_visual_tether_pos);
	//spaceship_visual_connect->attach(spaceshipPos,false);
	//spaceship_visual_tether->addComponent(spaceship_visual_connect);

	////Creating thing its tugging
	//Entity* ball = new Entity(); 
	//entities.push_back(ball);
	//physics_entities.push_back(ball);

	//PositionComp* ast_pos = new PositionComp(Vector3 (x-50,y,10), 0);
	//ball->addComponent(ast_pos);		
	//ball->addComponent(new SpriteComp (asteroid_bitmap,ast_pos));
	//PhysicsComp* ast_phys = new PhysicsComp (10,al_get_bitmap_width(asteroid_bitmap)/2,0.3,ast_pos);
	//ball->addComponent(ast_phys);

	//Entity* ball_visual_tether = new Entity();
	//entities.push_back(ball_visual_tether);
	//PositionComp* ball_visual_tether_pos = new PositionComp(Vector3(0,0,16));
	//ball_visual_tether->addComponent(ball_visual_tether_pos);
	//ball_visual_tether->addComponent(new SpriteComp(tether_bitmap,ball_visual_tether_pos));
	//ConnectedComp* ball_visual_connect = new ConnectedComp(0,10,ast_pos,ball_visual_tether_pos);
	//ball_visual_connect->attach(ast_pos,false);
	//ball_visual_tether->addComponent(ball_visual_connect);

	//Entity* tether = new Entity();
	//entities.push_back(tether);
	//tether->addComponent(new TetherComp(100,spaceshipPos,spaceship_Phys,30,PI, ast_pos,ast_phys,10,0));

	return spaceship_combiner;
};
void SpaceSim::CreateAsteroid()
{
	Entity* ball = new Entity(); 
	entities.push_back(ball);
	physics_entities.push_back(ball);

	double x = std::rand()%(screen_width-100)+50;
	double y = -(std::rand()%(screen_height-100)+50);

	PositionComp* ast_pos = new PositionComp(Vector3 (x,y,10), 0);
	ball->addComponent(ast_pos);		
	ball->addComponent(new SpriteComp (asteroid_bitmap,ast_pos));
	ball->addComponent(new PhysicsComp (10,al_get_bitmap_width(asteroid_bitmap)/2,0.3,ast_pos));
};
void SpaceSim::CreateDebris()
{
	Entity* debris = new Entity(); 
	entities.push_back(debris);
	physics_entities.push_back(debris);

	double x = std::rand()%(screen_width-800)+600;
	double y = -(std::rand()%(screen_height-800)+300);

	PositionComp* deb_pos = new PositionComp(Vector3 (x,y,10), 0);
	debris->addComponent(deb_pos);		
	debris->addComponent(new SpriteComp (debris_bitmap,deb_pos));
	debris->addComponent(new PhysicsComp (0.00001,al_get_bitmap_width(debris_bitmap)/2,0.7,deb_pos));
};

void SpaceSim::UnloadContent()
{
	al_destroy_font(font24);

	//al_destroy_bitmap(astronaut_bitmap);
	al_destroy_bitmap(asteroid_bitmap );

	/*al_destroy_sample(co2_left_sample);
	al_destroy_sample(co2_right_sample);
	al_destroy_sample(co2_sample);
	al_destroy_sample(co2_back_sample);
	al_destroy_sample_instance(co2_left_sample_instance);
	al_destroy_sample_instance(co2_right_sample_instance);
	al_destroy_sample_instance(co2_sample_instance);
	al_destroy_sample_instance(co2_back_sample_instance);*/

	al_destroy_display(display);

	for(int p = 0 ; p < entities.size(); p++)
	{
		delete(entities[p]);
	}
};

void SpaceSim::Update()
{
	while(!done)
	{
		//Delta time handling
		double current_timestamp = al_get_time();
		double seconds_since_last_tick = current_timestamp - previous_tick_timestamp;
		/*if(seconds_since_last_tick > .25)
		{
		seconds_since_last_tick = 0.25;
		}*/
		previous_tick_timestamp = current_timestamp;
		accumulator+=seconds_since_last_tick;

		//Do this before drawing
		while ( accumulator >= dt )
		{
			TakeInput();

			//Update all the entities
			for(std::vector<Entity*>::size_type i = 0; i != entities.size(); i++) 
			{
				entities[i]->update(dt);

				/*if(entities[i]->hasComponent("Removal"))
				{
				RemovalComp* remove = (RemovalComp*)entities[i]->getComponent("Removal");
				if(remove->getShouldDiscard())
				{
				entities.erase(entities.begin() + i);
				i--;
				}
				}*/
			}

			//CHECKING COLLISION and wrap 
			for(int i = 0; i != physics_entities.size(); i++) 
			{
				/*if(physics_entities[i]->hasComponent("Removal"))
				{
				RemovalComp* remove = (RemovalComp*)physics_entities[i]->getComponent("Removal");
				if(remove->getShouldDiscard())
				{
				physics_entities.erase(physics_entities.begin() + i);
				}
				}*/

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
					//done = true;
				}
				//Left
				if( (pos->getPosition().x + al_get_bitmap_width (spr->getBitmap())/2 ) < 0)
				{
					pos->setPositionX(pos->getPosition().x + al_get_bitmap_width (spr->getBitmap())/2 + screen_width);
					//done = true;
				}
				//Top
				if( (pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 ) > 0)
				{
					pos->setPositionY(pos->getPosition().y + al_get_bitmap_height(spr->getBitmap())/2 - screen_height);
					//done = true;
				}
				//Bottom
				if( (pos->getPosition().y + al_get_bitmap_height (spr->getBitmap())/2 ) < -screen_height)
				{
					pos->setPositionY(pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 + screen_height);
					//done = true;
				}

			}
			/*UpdateUI();*/
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
	Entity* spaceship_body =  spaceship->getEntity("body");
	PositionComp* spaceship_body_pos = (PositionComp*) spaceship_body->getComponent("Position");
	PhysicsComp* spaceship_body_physiscs = (PhysicsComp*)spaceship_body->getComponent("Physics");

	//WASD
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
	{
		Entity* thruster_main_entity = spaceship->getEntity("thruster_main");
		PositionComp* thruster_main_pos = (PositionComp*) thruster_main_entity->getComponent("Position");
		ThrusterComp* thruster_main = (ThrusterComp*)thruster_main_entity->getComponent("Thruster");
		ConnectedComp* thruster_main_connected = (ConnectedComp*)thruster_main_entity->getComponent("Connected");

		spaceship_body_physiscs->addForce(Force(thruster_main_connected->getRadianFromSocket()+spaceship_body_pos->getRotation(),
			thruster_main_pos->getRotation(),
			thruster_main->getForceExerted()));
	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_D))
	{
		Entity* thruster_east_entity = spaceship->getEntity("thruster_east");
		PositionComp* thruster_east_pos = (PositionComp*) thruster_east_entity->getComponent("Position");
		ThrusterComp* thruster_east = (ThrusterComp*)thruster_east_entity->getComponent("Thruster");
		ConnectedComp* thruster_east_connected = (ConnectedComp*)thruster_east_entity->getComponent("Connected");

		spaceship_body_physiscs->addForce(Force(thruster_east_connected->getRadianFromSocket()+spaceship_body_pos->getRotation(),
			thruster_east_pos->getRotation(),
			thruster_east->getForceExerted()));

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_S))
	{

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_A))
	{
		Entity* thruster_west_entity = spaceship->getEntity("thruster_west");
		PositionComp* thruster_west_pos = (PositionComp*) thruster_west_entity->getComponent("Position");
		ThrusterComp* thruster_west = (ThrusterComp*)thruster_west_entity->getComponent("Thruster");
		ConnectedComp* thruster_west_connected = (ConnectedComp*)thruster_west_entity->getComponent("Connected");

		spaceship_body_physiscs->addForce(Force(thruster_west_connected->getRadianFromSocket()+spaceship_body_pos->getRotation(),
			thruster_west_pos->getRotation(),
			thruster_west->getForceExerted()));
	}

	//ARROW KEYS
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_UP))
	{
		if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_UP))
		{
			Entity* north_turret_entity = spaceship->getEntity("turret_north");
			PositionComp* north_turret_pos = (PositionComp*) north_turret_entity->getComponent("Position");
			TurretComp* north_turret = (TurretComp*) north_turret_entity->getComponent("Turret");

			Entity* bullet = new Entity();
			physics_entities.push_back(bullet);
			entities.push_back(bullet);

			//We need to allow space betweent he turret and the bullet so they dont collide
			double x_position = (15.0*cos(north_turret_pos->getRotation())) + north_turret_pos->getPosition().x;
			double y_position = (15.0*sin(north_turret_pos->getRotation())) + north_turret_pos->getPosition().y;

			PositionComp* bullet_pos = new PositionComp(Vector3(x_position,y_position,16));
			bullet->addComponent(bullet_pos);
			bullet->addComponent(new SpriteComp(bullet_bitmap,bullet_pos));
			bullet->addComponent(new BulletComp(north_turret->getBulletArmorPiercing()));
			//bullet->addComponent(new RemovalComp(3,false,bullet));

			PhysicsComp* bullet_phys =new PhysicsComp(north_turret->getBulletWeight(),al_get_bitmap_width(bullet_bitmap)/2,.1,bullet_pos);
			double bullet_direction = north_turret_pos->getRotation();
			double bullet_degrees = bullet_direction*57.2957795;
			bullet_phys->addForce(Force(bullet_direction+PI,bullet_direction, north_turret->getBulletForce()));
			bullet->addComponent(bullet_phys);

		}
	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_RIGHT))
	{
		if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_RIGHT))
		{

		}
	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_DOWN))
	{

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_LEFT))
	{
		if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_LEFT))
		{

		}
	}


	////Q
	//if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_Q))
	//{
	//	if(!al_key_down(&old_keyboard_state,ALLEGRO_KEY_Q))
	//	{
	//		player_sprite->setBitmap(dead_bitmap);
	//	}
	//}

	////Player fuel stats

	//double fuel_cost =player_astronaut->getFuelCost();
	//double current_co2 = player_astronaut->getCurrentCO2();

	////W
	//current_co2 = player_astronaut->getCurrentCO2();
	//if(current_co2 > fuel_cost*1000*dt && al_key_down(&new_keyboard_state,ALLEGRO_KEY_W))
	//{
	//	thrust_animated->setToVisible();
	//	player_physics->addForce(Force(player_position->getRotation()+PI,player_position->getRotation(),1000));
	//	if(!al_get_sample_instance_playing(co2_sample_instance))
	//	{
	//		al_play_sample_instance(co2_sample_instance);
	//	}		

	//	player_astronaut->setCurrentCO2(current_co2 - (fuel_cost*1000)*dt );
	//}
	//else
	//{
	//	thrust_animated->setToInvisible();
	//	al_stop_sample_instance(co2_sample_instance);
	//}

	////S
	//current_co2 = player_astronaut->getCurrentCO2();
	//if(current_co2 > fuel_cost*1000*dt && al_key_down(&new_keyboard_state,ALLEGRO_KEY_S))
	//{
	//	double current_co2 = player_astronaut->getCurrentCO2();

	//	thrust_back_animated->setToVisible();
	//	player_physics->addForce(Force(player_position->getRotation(),player_position->getRotation()+PI,1000));

	//	if(!al_get_sample_instance_playing(co2_sample_instance))
	//	{
	//		al_play_sample_instance(co2_back_sample_instance);
	//	}	
	//	player_astronaut->setCurrentCO2(current_co2 - (fuel_cost*1000)*dt );
	//}
	//else
	//{
	//	thrust_back_animated->setToInvisible();
	//	al_stop_sample_instance(co2_back_sample_instance);
	//}

	////D
	//current_co2 = player_astronaut->getCurrentCO2();
	//if(current_co2 > fuel_cost*500*dt && al_key_down(&new_keyboard_state,ALLEGRO_KEY_D))
	//{

	//	thrust_right_animated->setToVisible();
	//	player_physics->addForce(Force(player_position->getRotation()-(PI/2.0),player_position->getRotation(),500));
	//	if(!al_get_sample_instance_playing(co2_right_sample_instance))
	//	{
	//		al_play_sample_instance(co2_right_sample_instance);
	//	}	
	//	player_astronaut->setCurrentCO2(current_co2 - (fuel_cost*500)*dt );
	//}
	//else
	//{
	//	thrust_right_animated->setToInvisible();
	//	al_stop_sample_instance(co2_right_sample_instance);
	//}

	////A
	//current_co2 = player_astronaut->getCurrentCO2();
	//if(current_co2 > fuel_cost*500*dt && al_key_down(&new_keyboard_state,ALLEGRO_KEY_A))
	//{
	//	thrust_left_animated->setToVisible();
	//	player_physics->addForce(Force(player_position->getRotation()+(PI/2.0),player_position->getRotation(),500));
	//	if(!al_get_sample_instance_playing(co2_sample_instance))
	//	{
	//		al_play_sample_instance(co2_left_sample_instance);
	//	}	
	//	player_astronaut->setCurrentCO2(current_co2 - (fuel_cost*500)*dt );	
	//}
	//else
	//{
	//	thrust_left_animated->setToInvisible();
	//	al_stop_sample_instance(co2_left_sample_instance);
	//}


	old_keyboard_state = new_keyboard_state;
}

void SpaceSim::UpdateUI()
{
	//double co2_ticks_worth = 100/player_astronaut->getMaxCO2();
	//double visible_bars_co2 = player_astronaut->getCurrentCO2()/co2_ticks_worth;

	//double o2_ticks_worth = 100/player_astronaut->getMaxO2();
	//double visible_bars_o2 = player_astronaut->getCurrentO2()/o2_ticks_worth;

	//for(int p = 0 ; p < 100 ; p++)
	//{
	//	//CO2 UPDATE
	//	Entity* co2_bar = co2_bars[p];

	//	SpriteComp* spr = (SpriteComp*) co2_bar->getComponent("Sprite");
	//	if(p<=visible_bars_co2)
	//	{
	//		//If its within curret
	//		spr->setToVisible();
	//	}
	//	else
	//	{
	//		//If its greater than current
	//		spr->setToInvisible();
	//	}

	//	//O2 UPDATE
	//	Entity* o2_bar = oxygen_bars[p];
	//	spr = (SpriteComp*) o2_bar->getComponent("Sprite");
	//	if(p<=visible_bars_o2)
	//	{
	//		//If its within curret
	//		spr->setToVisible();
	//	}
	//	else
	//	{
	//		//If its greater than current
	//		spr->setToInvisible();
	//	}
	//}
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