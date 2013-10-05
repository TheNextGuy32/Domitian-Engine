#include "Component.h"
#include "Entity.h"

Component::Component(std::string myName,Entity* myParent):parent(myParent),name(myName)
{
	
}

Component* Component::getComponent(std::string myCompName)
{
	return parent->getComponent(myCompName);
}

std::string Component::getName()
{
	return name;
}
void Component::update(float dt)
{
}