#ifndef DComp_H
#define DComp_H

#include "Entity.h"

#include <string>
#include "Vector2.h"
#include "Vector3.h"


class Component
{
public:
	virtual void update(double);
	Component(std::string);
	std::string getName();
	Entity* getParent()
	{
		return parent;
	};
	void setParent(Entity* myParent)
	{
		parent = myParent;
	};
	Component* getComponent(std::string myCompName)
	{
		return getParent()->getComponent(myCompName);
	};

	
private:
	std::string name;
	Entity* parent;
};

#endif