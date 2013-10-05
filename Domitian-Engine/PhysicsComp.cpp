#include "PhysicsComp.h"
#include "PositionComp.h"

PhysicsComp::PhysicsComp(float myMass, Entity* myParent):Component("Physics",myParent),mass(myMass)
{
	
}


void PhysicsComp::update(float dt)
{
	PositionComp* posComp = (PositionComp*) getComponent("Position");

	//float total_mass = 0 + physics->getMass();
	//			float total_translation [2] = {0,0};

	//			float moment_of_inertia = 0 + physics->getMass();
	//			float total_torque = 0;

	//			if( controlled_entities[i]->checkIfHasComponent("Collection"))
	//			{
	//				CollectionComponent* collection = (CollectionComponent*) controlled_entities[i]->getComponent("Collection");
	//				vector<Entity*> attached_entities = collection->getAttachedEntities();

	//				//Cycling through attached entities
	//				for(vector<Entity*>::size_type p = 0; p != attached_entities.size(); p++) 
	//				{
	//					Entity* attached_entity = attached_entities[p];

	//					TetheredComponent* tethered = (TetheredComponent*) attached_entity->getComponent("Tethered");
	//					PhysicsComponent* attached_physics = (PhysicsComponent*) attached_entity->getComponent("Physics");
	//					PositionComponent* attached_position = (PositionComponent*) attached_entity->getComponent("Position");
	//					RocketComponent* rocket = (RocketComponent*) attached_entity->getComponent("Rocket");

	//					float radian_from_center_mass = tethered->getDirectionRadian();
	//					float radian_to_center_mass = radian_from_center_mass + 3.1415926;
	//					float t = attached_position->getAngle() - radian_to_center_mass ;
	//			
	//					tethered->setT(t);

	//					//Translational
	//					vector<float> attached_vector_forces = attached_physics->getNetTranslationalForce();
	//					total_translation[0] += attached_vector_forces[0];
	//					total_translation[1] += attached_vector_forces[1];
	//				
	//					total_mass+= attached_physics->getMass();

	//					//Angular
	//					float attached_net_angular_force = attached_physics->getNetAngularForce();
	//					total_torque += attached_net_angular_force;

	//					float distance = tethered->getDistance();
	//					moment_of_inertia += attached_physics->getMass()*(distance*distance);
	//				}
	//		
	//			}

	//			//Apparently on forces that have a distance can spin it
	//			//So after we've pulled all the angular forces we can find the angular acceleration

	//			//and then you use torque = I*a

	//			physics->setAngularAcceleration(total_torque/moment_of_inertia);
	//	

	//			//PLANAR MOVEMENT

	//			//We already have the tethered objects' forces so now we need the forces affectin the main object itself
	//			vector<float> vector_forces = physics->getNetTranslationalForce();
	//			total_translation[0] += vector_forces[0];
	//			total_translation[1] += vector_forces[1];
	//	

	//			//Calculating the net acceleration net forces and net mass
	//			physics->setAccelerationX(total_translation[0]/total_mass);
	//			physics->setAccelerationY(total_translation[1]/total_mass);

	//			//Determine its new velocity
	//			physics->setVelocityX(physics->getVelocity()[0]+physics->getAcceleration()[0]*time_since_last_tick);
	//			physics->setVelocityY(physics->getVelocity()[1]+physics->getAcceleration()[1]*time_since_last_tick);

	//			//Determine its new position if its not tethered to something
	//			if( !controlled_entities[i]->checkIfHasComponent("Tethered"))
	//			{
	//				position->setX(position->getPosition()[0]+physics->getVelocity()[0]*time_since_last_tick);
	//				position->setY(position->getPosition()[1]+physics->getVelocity()[1]*time_since_last_tick);
	//			}
	//		
	//			//ANGULAR MOVEMENT
	//			//	Both tethered and collected entities get this because a tethered can be rotating on its own
	//			//	on top of being rotated by the collectors movement.
	//			//  On it's own, a tethered object cannot have an angular acceleration, it must be machine assisted.
	//	
	//			physics->setAngularVelocity(physics->getAngularVelocity()+physics->getAngularAcceleration()*time_since_last_tick);
	//			position->setAngle(position->getAngle()+physics->getAngularVelocity()*time_since_last_tick);

	//			//To make sure the tethered objects get moved we make sure the collector handles them we he is passed into this controller
	//			if( controlled_entities[i]->checkIfHasComponent("Collection"))
	//			{
	//				CollectionComponent* collection = (CollectionComponent*) controlled_entities[i]->getComponent("Collection");
	//				vector<Entity*> attached_entities = collection->getAttachedEntities();

	//				//Go throuhg all the attached entities and update their tethered position wiht the new positon of the collector
	//				for(vector<Entity*>::size_type p = 0; p != attached_entities.size(); p++) 
	//				{
	//					Entity* attached_entity = attached_entities[p];

	//					TetheredComponent* tethered = (TetheredComponent*) attached_entity->getComponent("Tethered");
	//					PhysicsComponent* attached_physics = (PhysicsComponent*) attached_entity->getComponent("Physics");
	//					PositionComponent* attached_position = (PositionComponent*) attached_entity->getComponent("Position");

	//					////Determine its new position

	//					//As the object spins so will all the tethered objects
	//					tethered->setDirectionRadian( tethered->getDirectionRadian() + physics->getAngularVelocity()*time_since_last_tick);

	//					float radian_from_center_mass = tethered->getDirectionRadian();
	//					float radian_to_center_mass = radian_from_center_mass + 3.1415926;
	//					attached_position->setAngle(radian_to_center_mass + tethered->getT());
	//			
	//					//Need to update the angle of the rocket as the main ship spins

	//					//Set the tethered object to the new position in the new direction
	//					attached_position->setX( position->getPosition()[0] + cos(tethered->getDirectionRadian())*tethered->getDistance());
	//					attached_position->setY( position->getPosition()[1] + sin(tethered->getDirectionRadian())*tethered->getDistance());
	//				}
	//			}
	//			position->calculateBucketPosition(BUCKET_WIDTH);

	posComp->setPositionX(posComp->getPosition().x + total_force.x*dt);
	posComp->setPositionY(posComp->getPosition().y + total_force.y*dt);
}