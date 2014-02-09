#include "Entity.h"
#include "Component.h"

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

void Entity::addComponent(Component* myComp)
{
	components[myComp->getName()] = myComp;
}
void Entity::removeEntity(std::string myCompName)
{

}
std::string Entity::getName()
{
	return name;
}

Component* Entity::getComponent(std::string myCompName)
{
	return components[myCompName];
}