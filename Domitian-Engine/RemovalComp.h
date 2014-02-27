//A bool for whether or not we should dicard this entity
//If set, a timer before removal
//If set, a condition to be met before timer begins

#ifndef RemovalComp_H
#define RemovalComp_H

#include "Component.h"

class RemovalComp : public Component
{
public:
	RemovalComp(bool myHasCondition,Entity* myParent);
	RemovalComp(double myMaxTimer, bool myHasCondition,Entity* myParent);

	void update(double dt);

	void meetCondition();
	bool getShouldDiscard();
private:
	bool should_discard;
	bool has_condition;
	bool has_met_condition;
	bool has_timer;
	
	double current_timer;
	double max_timer;
};

#endif