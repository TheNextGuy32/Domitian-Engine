#ifndef DConnectedComp_H
#define DConnectedComp_H

#include "Entity.h"
#include "Component.h"
#include "PositionComp.h"
#include "Radian.h"

class ConnectedComp : public Component
{
public:
	
	ConnectedComp(float myRadianFromSocket,float myDistance,Entity* myParent);
	void update(float);

	bool attach(PositionComp* mySocket)
	{
		if(connected)
		{
			return false;
		}
		else
		{
			socket_position = mySocket;
			connected = true;
		}
	};
	bool detach()
	{
		if (connected)
		{
			connected = false;
			return true;
		}
		else
		{
			return false;
		}
	};

private:
	PositionComp* socket_position;
	PositionComp* connected_position;

	bool connected;
	float radian_from_socket;
	float distance;


};
#endif