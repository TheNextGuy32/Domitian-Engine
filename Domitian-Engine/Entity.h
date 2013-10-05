#ifndef DEntity_H
#define DEntity_H

#include <string>
#include <vector>
#include <unordered_map>

class Component;

class Entity
{
public:
	void update(float);

	void addEntity(Component*);
	void removeEntity(std::string);
	std::string getName();

	Component* getComponent(std::string);

private:
	bool active;
	std::string name;

	std::unordered_map<std::string,Component*> components;

};

#endif