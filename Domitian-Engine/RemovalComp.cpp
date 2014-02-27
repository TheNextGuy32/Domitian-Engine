#include "RemovalComp.h"

RemovalComp::RemovalComp(bool myHasCondition,Entity* myParent)
	:Component("Removal",myParent),has_condition(myHasCondition)
{
	has_met_condition = false;
	has_timer = false;
	should_discard = false;
	
};
RemovalComp::RemovalComp(double myMaxTimer, bool myHasCondition,Entity* myParent)
	:Component("Removal",myParent),has_condition(myHasCondition),max_timer(myMaxTimer)
{
	has_met_condition = false;
	current_timer= 0;
	has_timer = true;
	should_discard = false;
};

void RemovalComp::update(double dt)
{
	if(has_condition)
	{
		if(has_met_condition)
		{
			if(has_timer)
			{
				current_timer+=dt;
				if(max_timer<current_timer)
				{
					should_discard = true;
				}
			}
			else
			{
				should_discard = true;
			}
		}
	}
	else
	{
		if(has_timer)
		{
			current_timer+=dt;
			if(max_timer<current_timer)
			{
				should_discard = true;
			}
		}
	}	
};

void RemovalComp::meetCondition(){has_met_condition = true;};
bool RemovalComp::getShouldDiscard(){return should_discard;};