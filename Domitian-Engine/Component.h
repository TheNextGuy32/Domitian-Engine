#ifndef DComp_H
#define DComp_H

#include <string>
#include "Vector2.h"
#include "Vector3.h"

class Entity;

class Component
{
public:
	virtual void update(double);
	Component(std::string, Entity*);
	std::string getName();
	
	 Component* getComponent(std::string);

	 /*bool hasComponent(std::string componentName)
	{
		return parent->hasComponent(componentName);
	};*/
	 Entity* parent;
private:
	std::string name;
	
};

#endif