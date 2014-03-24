#include "Component.h"
#include "Entity.h"

Component::Component(std::string myName):name(myName)
{
	parent = new Entity();
}

std::string Component::getName()
{
	return name;
}
void Component::update(double dt)
{
}