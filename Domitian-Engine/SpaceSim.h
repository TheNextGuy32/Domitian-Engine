#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include "Domitian-Engine.h"

#include "AstronautComp.h"
#include "SpaceshipComp.h"
#include "BulletComp.h"
#include "TurretComp.h"
#include "ThrusterComp.h"
#include "TetherComponent.h"

#include "Combiner.h"
#include "RemovalComp.h"

#include <iostream>

#pragma region Preproccessor

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#define deg2rad( a ) a * (PI/180)

#pragma endregion

class SpaceSim{


public:
	SpaceSim();
	void Initialize();

	void LoadContent();
	void LoadAllegro();

	void CreateWorld();
	void CreateDebris();
	void CreateAsteroid();
	void CreatePlayer();
	Combiner* CreateSpaceship(double x, double y);
	void CreateSpaceStation();
	void CreateGUI();

	void UnloadContent();

	void Update();
	void TakeInput();
	void UpdateUI();

	void Draw();
	void DrawScreenNodes();

private:

	//std::string game_state;

	boolean done;

	double FPS;
	double total_frames;
	double previous_tick_timestamp;
	double elapsed_time;
	double old_time;

	double dt;
	double doubledt;
	double accumulator;

	ALLEGRO_KEYBOARD_STATE new_keyboard_state,old_keyboard_state;
	ALLEGRO_DISPLAY* display;
	int screen_width;
	int screen_height;

	ALLEGRO_FONT* font24;

	/*ALLEGRO_BITMAP* red_ball;
	ALLEGRO_BITMAP* maroon_ball;*/

	/*ALLEGRO_BITMAP* astronaut_bitmap;
	ALLEGRO_BITMAP* dead_bitmap;*/

	ALLEGRO_BITMAP* asteroid_bitmap;
	ALLEGRO_BITMAP* debris_bitmap;

	ALLEGRO_BITMAP* thrust_bitmap;

	ALLEGRO_BITMAP* spaceship_bitmap;
	ALLEGRO_BITMAP* turret_bitmap;
	ALLEGRO_BITMAP* bullet_bitmap;
	ALLEGRO_BITMAP* tether_bitmap;

	/*ALLEGRO_BITMAP* iss_bitmap;
	ALLEGRO_BITMAP* iss_plus_bitmap;

	ALLEGRO_BITMAP* co2_bar_bitmap;
	ALLEGRO_BITMAP* oxygen_bar_bitmap;
	ALLEGRO_BITMAP* gui_bar_bitmap;

	ALLEGRO_SAMPLE* co2_sample;
	ALLEGRO_SAMPLE_INSTANCE* co2_sample_instance;

	ALLEGRO_SAMPLE* co2_back_sample;
	ALLEGRO_SAMPLE_INSTANCE* co2_back_sample_instance;

	ALLEGRO_SAMPLE* co2_left_sample;
	ALLEGRO_SAMPLE_INSTANCE* co2_left_sample_instance;

	ALLEGRO_SAMPLE* co2_right_sample;
	ALLEGRO_SAMPLE_INSTANCE* co2_right_sample_instance;*/

	//std::unordered_map<std::string,std::vector<Entity*>> game_state_entities;
	std::vector<Entity*> entities;
	std::vector<Entity*> physics_entities;

	/*Entity* player;
	PositionComp* player_position;
	SpriteComp* player_sprite;
	PhysicsComp* player_physics;
	AstronautComp* player_astronaut;

	Entity* thrust;
	AnimatedComp* thrust_animated;
	PositionComp* thrust_position;
	ConnectedComp* thrust_connected;

	Entity* thrust_back;
	PositionComp* thrust_back_position;
	AnimatedComp* thrust_back_animated;
	ConnectedComp* thrust_back_connected;

	Entity* thrust_right;
	PositionComp* thrust_right_position;
	AnimatedComp* thrust_right_animated;
	ConnectedComp* thrust_right_connected;

	Entity* thrust_left;
	PositionComp* thrust_left_position;
	AnimatedComp* thrust_left_animated;
	ConnectedComp* thrust_left_connected;*/

	Combiner* spaceship;
	//Entity* satellite;

	/*Entity* oxygen_bars[100];
	Entity* co2_bars[100];*/
};