#ifndef DGroupComp_H
#define DGroupComp_H

#include "Component.h"
#include "Entity.h"

#include "PositionComp.h"

class GroupComp : public Component
{
public:
	GroupComp(Entity*);
	update(float);

private:
	std::vector<Entity*> members;

};


#endif