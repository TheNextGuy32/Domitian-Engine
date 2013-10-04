#include <string>
#include <vector>
#include <unordered_map>

#include "Component.h"

class Entity
{
public:
	void Update();
	
private:
	bool active;
	std::string name;

	std::unordered_map<std::string,Component*> components;
	//std::vector<Component*> components;
};