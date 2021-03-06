#ifndef DConnectedComp_H
#define DConnectedComp_H

#include "Component.h"
#include "PositionComp.h"

class ConnectedComp : public Component
{
public:
	ConnectedComp(double myRadianFromSocket,double myDistance, PositionComp* mySocketPositionComp,PositionComp* myLesserPos);
	void update(double);
	
	double getRadianFromSocket(){return radian_from_socket;};

	bool attach(PositionComp* mySocket, bool myHandleRotation);
	bool detach();

private:
	PositionComp* socket_position;//The larger thing we are attached to: the body
	PositionComp* connected_position;//The thing that is attaced: the arm

	double old_socket_rotation, new_socket_rotation;

	bool connected,handle_rotation;
	double radian_from_socket;
	double distance;
};
#endif