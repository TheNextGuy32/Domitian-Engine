#ifndef DComp_H
#define DComp_H

#include <string>
#include "Vector2.h"
#include "Vector3.h"

class Entity;

class Component
{
public:
	virtual void update(float);
	Component(std::string, Entity*);
	std::string getName();
	
	Component* getComponent(std::string);

private:
	std::string name;
	Entity* parent;
};

#endif