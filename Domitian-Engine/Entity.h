#ifndef DEntity_H
#define DEntity_H

#include <string>
#include <vector>
#include <unordered_map>

class Component;

class Entity
{
public:
	Entity();
	Entity(std::string myName);

	std::string getName();

	void update(double);
	void draw(double dt);

	void addComponent(Component*);
	void removeEntity(std::string);

	Component* getComponent(std::string);
	bool hasComponent(std::string componentName)
	{
		for (auto it = components.begin(); it != components.end(); ++it) 
		{
			if(it->first == componentName) return true;
		}
		return false;
	};

private:
	bool active;
	std::string name;

	std::unordered_map<std::string,Component*> components;

};

#endif