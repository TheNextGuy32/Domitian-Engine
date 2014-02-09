#ifndef DGroupComp_H
#define DGroupComp_H

#include "Component.h"
class Entity;
#include "PositionComp.h"

#include <vector>

class GroupComp : public Component
{
public:
	GroupComp(Entity*);
	void update(double);

private:
	std::vector<Entity*> members;

};


#endif