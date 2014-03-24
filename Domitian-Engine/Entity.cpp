#include "Entity.h"
#include "Component.h"

Entity::Entity(){};
Entity::Entity(std::string myName){name = myName;};

std::string Entity::getName(){return name;};

void Entity::update(double dt)
{
	for (auto it = components.begin(); it != components.end(); ++it) 
	{
		if(it->first != "Sprite" && it->first != "Animated")
		{
			it->second->update(dt);
		}
	}
}

void Entity::draw(double dt)
{
	for (auto it = components.begin(); it != components.end(); ++it) 
	{
		if(it->first == "Sprite" || it->first == "Animated")
		{
			it->second->update(dt);
		}
	}
}
Component* Entity::getComponent(std::string myCompName)
{
	return components[myCompName];
}


void Entity::addComponent(Component* myComp)
{
	components[myComp->getName()] = myComp;
	components[myComp->getName()]->setParent(this);
}

