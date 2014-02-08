#ifndef DConnectedComp_H
#define DConnectedComp_H

#include "Component.h"
#include "PositionComp.h"

class ConnectedComp : public Component
{
public:
	ConnectedComp(float myRadianFromSocket,float myDistance,Entity* myParent, PositionComp* mySocketPositionComp);
	void update(float);

	bool attach(PositionComp* mySocket, bool myHandleRotation);
	bool detach();

private:
	PositionComp* socket_position;//The larger thing we are attached to: the body
	PositionComp* connected_position;//The thing that is attaced: the arm

	float old_socket_rotation, new_socket_rotation;

	bool connected,handle_rotation;
	float radian_from_socket;
	float distance;
};
#endif