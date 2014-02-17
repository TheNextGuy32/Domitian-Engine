#include "Combiner.h"

void Combiner::addEntity(std::string myName, Entity* myEntity)
{
	combined[myName] = myEntity;
};

bool Combiner::hasEntity(std::string myName)
{
	for (auto it = combined.begin(); it != combined.end(); ++it) 
	{
		if(it->first == myName)
		{
			return true;
		}
	}
	return false;
};

Entity* Combiner::getEntity(std::string myName)
{
	return combined[myName];
};