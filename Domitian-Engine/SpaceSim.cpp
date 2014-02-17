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

	/*red_ball = al_load_bitmap("fighter.png");
	maroon_ball = al_load_bitmap("fightermaroon.png");

	astronaut_bitmap = al_load_bitmap("astronaut.png");
	dead_bitmap = al_load_bitmap("dead_astronaut.png");*/

	asteroid_bitmap = al_load_bitmap("asteroid.png");
	debris_bitmap = al_load_bitmap("debris.png");

	thrust_bitmap = al_load_bitmap("co2.png");

	/*iss_bitmap = al_load_bitmap("iss_piece.png");
	iss_plus_bitmap = al_load_bitmap("iss_plus.png");*/

	spaceship_bitmap= al_load_bitmap("spaceship.png");
	turret_bitmap = al_load_bitmap("turret.png");
	bullet_bitmap = al_load_bitmap("debris.png");

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
	////for(int p = 0 ; p <0; p++)
	////{
	////	CreateAsteroid();

	////}
	///*for(int p = 0 ; p < 20; p++)
	//{
	//	CreateDebris();
	//}*/
	//CreateSpaceStation();
	//CreateGUI();

	spaceship = CreateSpaceship(300,-300);
};
void SpaceSim::CreatePlayer()
{
	//Entity* player = new Entity();

	//entities.push_back(player);
	//physics_entities.push_back(player);

	//player_position = new PositionComp (Vector3 (200,-200,10), 0, player);
	//player->addComponent(player_position);

	//player_sprite = new SpriteComp (astronaut_bitmap, player);
	//player->addComponent(player_sprite);

	//player_physics = new PhysicsComp (10,al_get_bitmap_width(astronaut_bitmap)/2,player);
	//player->addComponent(player_physics);

	//player_astronaut = new AstronautComp(100,0.001,100,1,player);
	//player->addComponent(player_astronaut);

	//// Thrust
	//thrust = new Entity();
	//entities.push_back(thrust);

	//thrust_position = new PositionComp (Vector3 (100,-100,10),0,thrust);
	//thrust->addComponent(thrust_position);

	//thrust_animated = new AnimatedComp (thrust_bitmap,Vector2(30,80),thrust);
	//thrust->addComponent(thrust_animated);

	//thrust_connected = new ConnectedComp (player_position->getRotation()-(PI),player_physics->getRadius(),thrust,player_position);
	//thrust_connected->attach(player_position,true);
	//thrust->addComponent(thrust_connected);

	//// Back thrust
	//thrust_back = new Entity();
	//entities.push_back(thrust_back);

	//thrust_back_position = new PositionComp (Vector3 (100,-100,10),PI,thrust);
	//thrust_back->addComponent(thrust_back_position);

	//thrust_back_animated = new AnimatedComp(thrust_bitmap,Vector2(30,80),thrust_back);
	//thrust_back->addComponent(thrust_back_animated);

	//thrust_back_connected = new ConnectedComp (player_position->getRotation(),player_physics->getRadius(),thrust_back,player_position);
	//thrust_back_connected->attach(player_position,true);
	//thrust_back->addComponent(thrust_back_connected);

	////Right Thrust
	//thrust_right = new Entity();
	//entities.push_back(thrust_right);

	//thrust_right_position = new PositionComp (Vector3 (100,-100,10),0,thrust_right);
	//thrust_right->addComponent(thrust_right_position);

	//thrust_right_animated = new AnimatedComp (thrust_bitmap,Vector2(30,80),thrust_right);
	//thrust_right->addComponent(thrust_right_animated);

	//thrust_right_connected = new ConnectedComp (player_position->getRotation()-(PI/2.0),player_physics->getRadius(),thrust_right,player_position);
	//thrust_right_connected->attach(player_position,true);
	//thrust_right->addComponent(thrust_right_connected);

	////Left Thrust
	//thrust_left = new Entity();
	//entities.push_back(thrust_left);

	//thrust_left_position = new PositionComp (Vector3 (100,-100,10),0,thrust_left);
	//thrust_left->addComponent(thrust_left_position);

	//thrust_left_animated = new AnimatedComp (thrust_bitmap,Vector2(30,80),thrust_left);
	//thrust_left->addComponent(thrust_left_animated);

	//thrust_left_connected = new ConnectedComp (player_position->getRotation()+(PI/2.0),player_physics->getRadius(),thrust_left,player_position);
	//thrust_left_connected->attach(player_position,true);
	//thrust_left->addComponent(thrust_left_connected);
};
Combiner* SpaceSim::CreateSpaceship(double x, double y)
{
	Combiner* spaceship_combiner = new Combiner();

	//BODY
	Entity* spaceship = new Entity();
	entities.push_back(spaceship);
	physics_entities.push_back(spaceship);
	spaceship_combiner->addEntity("body",spaceship);

	PositionComp* spaceshipPos = new PositionComp(Vector3(x,y,15),0,spaceship);
	spaceship->addComponent(spaceshipPos);
	spaceship->addComponent(new SpriteComp(spaceship_bitmap,spaceship));
	spaceship->addComponent(new SpaceshipComp(30.0,spaceship));
	spaceship->addComponent(new PhysicsComp(100,al_get_bitmap_width(spaceship_bitmap),spaceship));

	//TURRETS
	Entity* turret_north = new Entity();
	entities.push_back(turret_north);
	spaceship_combiner->addEntity("turret_north",turret_north);

	turret_north->addComponent(new PositionComp(Vector3(x,y,16),0,turret_north));
	turret_north->addComponent(new SpriteComp(turret_bitmap,turret_north));
	ConnectedComp* turret_north_connected = new ConnectedComp(0,al_get_bitmap_width(spaceship_bitmap),turret_north, spaceshipPos);
	turret_north_connected->attach(spaceshipPos,true);
	turret_north->addComponent(turret_north_connected);
	turret_north->addComponent(new TurretComp(10,500000,5,0.05,turret_north));

	Entity* turret_east = new Entity();
	entities.push_back(turret_east);
	spaceship_combiner->addEntity("turret_east",turret_east);

	turret_east->addComponent(new PositionComp(Vector3(x,y,16),-PI/2,turret_east));
	turret_east->addComponent(new SpriteComp(turret_bitmap,turret_east));
	ConnectedComp* turret_east_connected = new ConnectedComp(-PI/2,al_get_bitmap_width(spaceship_bitmap),turret_east, spaceshipPos);
	turret_east_connected->attach(spaceshipPos,true);
	turret_east->addComponent(turret_east_connected);
	turret_east->addComponent(new TurretComp(10,500,5,0.05,turret_east));

	Entity* turret_west = new Entity();
	entities.push_back(turret_west);
	spaceship_combiner->addEntity("turret_west",turret_west);

	turret_west->addComponent(new PositionComp(Vector3(x,y,16),PI/2,turret_west));
	turret_west->addComponent(new SpriteComp(turret_bitmap,turret_west));
	ConnectedComp* turret_west_connected = new ConnectedComp(PI/2,al_get_bitmap_width(spaceship_bitmap),turret_west, spaceshipPos);
	turret_west_connected->attach(spaceshipPos,true);
	turret_west->addComponent(turret_west_connected);
	turret_west->addComponent(new TurretComp(10,500,5,0.05,turret_west));

	//Thrusters!
	Entity* main_thruster = new Entity();
	entities.push_back(main_thruster);
	spaceship_combiner->addEntity("thruster_main",main_thruster);

	main_thruster->addComponent(new PositionComp(Vector3(0,0,16),main_thruster));
	main_thruster->addComponent(new AnimatedComp(thrust_bitmap,Vector2(30,80),main_thruster));
	ConnectedComp* main_thruster_connected = new ConnectedComp(PI,al_get_bitmap_width(spaceship_bitmap),main_thruster,spaceshipPos);
	main_thruster_connected->attach(spaceshipPos,true);
	main_thruster->addComponent(main_thruster_connected);
	main_thruster->addComponent(new ThrusterComp(1000,main_thruster));

	Entity* turn_thruster = new Entity();
	entities.push_back(turn_thruster);
	spaceship_combiner->addEntity("thruster_turn",turn_thruster);

	turn_thruster->addComponent(new PositionComp(Vector3(0,0,16),PI/4,turn_thruster));
	turn_thruster->addComponent(new AnimatedComp(thrust_bitmap,Vector2(30,80),turn_thruster));
	ConnectedComp* turn_thruster_connected = new ConnectedComp(PI/2,al_get_bitmap_width(spaceship_bitmap),turn_thruster,spaceshipPos);
	turn_thruster_connected->attach(spaceshipPos,true);
	turn_thruster->addComponent(turn_thruster_connected);
	turn_thruster->addComponent(new ThrusterComp(1000,turn_thruster));

	return spaceship_combiner;
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
	double y = -(std::rand()%(screen_height-600)+300);

	debris->addComponent(new PositionComp(Vector3 (x,y,10), 0, debris));		
	debris->addComponent(new SpriteComp (debris_bitmap, debris));
	debris->addComponent(new PhysicsComp (0.1,al_get_bitmap_width(debris_bitmap)/2,debris));
};
void SpaceSim::CreateSpaceStation()
{
	//spaceship = new Entity();
	//entities.push_back(spaceship);
	//physics_entities.push_back(spaceship);
	//spaceship->addComponent(new PositionComp(Vector3 (250,-500,10), -PI/4, spaceship));		
	//spaceship->addComponent(new SpriteComp (spaceship_bitmap, spaceship));
	//PhysicsComp* spaceship_phys = new PhysicsComp (1000000,al_get_bitmap_height(spaceship_bitmap)/2,spaceship);
	////spaceship_phys->addForce(Force(PI,-PI/2,5000000));
	//spaceship->addComponent(spaceship_phys);
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
	/*thrust_animated->setToInvisible();
	thrust_back_animated->setToInvisible();
	thrust_right_animated->setToInvisible();
	thrust_left_animated->setToInvisible();*/

	while(!done)
	{
		//Delta time handling
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

			//Update all the entities
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
				////Boundaries
				////Right
				//if( (pos->getPosition().x - al_get_bitmap_width (spr->getBitmap())/2 ) > screen_width)
				//{
				//	//pos->setPositionX(pos->getPosition().x - al_get_bitmap_width (spr->getBitmap())/2 - screen_width);
				//	//done = true;
				//}
				////Left
				//if( (pos->getPosition().x + al_get_bitmap_width (spr->getBitmap())/2 ) < 0)
				//{
				//	//pos->setPositionX(pos->getPosition().x + al_get_bitmap_width (spr->getBitmap())/2 + screen_width);
				//	//done = true;
				//}
				////Top
				//if( (pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 ) > 0)
				//{
				//	//pos->setPositionY(pos->getPosition().y + al_get_bitmap_height(spr->getBitmap())/2 - screen_height);
				//	//done = true;
				//}
				////Bottom
				//if( (pos->getPosition().y + al_get_bitmap_height (spr->getBitmap())/2 ) < -screen_height)
				//{
				//	//pos->setPositionY(pos->getPosition().y - al_get_bitmap_height (spr->getBitmap())/2 + screen_height);
				//	//done = true;
				//}

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
		Entity* thruster_turn_entity = spaceship->getEntity("thruster_turn");
		PositionComp* thruster_turn_pos = (PositionComp*) thruster_turn_entity->getComponent("Position");
		ThrusterComp* thruster_turn = (ThrusterComp*)thruster_turn_entity->getComponent("Thruster");
		ConnectedComp* thruster_turn_connected = (ConnectedComp*)thruster_turn_entity->getComponent("Connected");

		spaceship_body_physiscs->addForce(Force(thruster_turn_connected->getRadianFromSocket()+spaceship_body_pos->getRotation(),
			thruster_turn_pos->getRotation(),
			thruster_turn->getForceExerted()));

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_S))
	{

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_A))
	{

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

			bullet->addComponent(new PositionComp(Vector3(north_turret_pos->getPosition().x,north_turret_pos->getPosition().y,18),bullet));
			bullet->addComponent(new SpriteComp(bullet_bitmap,bullet));
			PhysicsComp* bullet_phys =new PhysicsComp(north_turret->getBulletWeight(),al_get_bitmap_width(bullet_bitmap),bullet);
			bullet_phys->addForce(Force(north_turret_pos->getRotation()+PI,north_turret_pos->getRotation(), north_turret->getBulletForce()));
			bullet->addComponent(bullet_phys);
			bullet->addComponent(new BulletComp(north_turret->getBulletArmorPiercing(),bullet));
		}
	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_RIGHT))
	{

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_DOWN))
	{

	}
	if(al_key_down(&new_keyboard_state,ALLEGRO_KEY_LEFT))
	{

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

	//al_draw_bitmap(gui_bar_bitmap,230,650,0);

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