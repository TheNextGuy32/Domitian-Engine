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

	bool attach(PositionComp* mySocket, bool myHandleRotation)
	{
		if(connected)
		{
			return false;
		}
		else
		{
			socket_position = mySocket;
			connected = true;
			handle_rotation = myHandleRotation;
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

	bool connected,handle_rotation;
	float radian_from_socket;
	float distance;


};
#endif