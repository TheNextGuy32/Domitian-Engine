#ifndef Combiner_H
#define Combiner_H

#include "Component.h"
#include <string>
#include <vector>
#include <unordered_map>

class Combiner
{
public:
	void addEntity(std::string myName, Entity* myEntity);
	bool hasEntity(std::string myName);
	Entity* getEntity(std::string myName);

private:
	std::unordered_map<std::string,Entity*> combined;
};

#endif