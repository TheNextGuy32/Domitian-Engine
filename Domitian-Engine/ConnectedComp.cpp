#include "ConnectedComp.h"


// W/ socket
ConnectedComp::ConnectedComp(double myRadianFromSocket, double myDistance, PositionComp* mySocketPositionComp)
	: Component("Connected"), distance(myDistance),radian_from_socket(myRadianFromSocket), socket_position(mySocketPositionComp)
{
	connected_position = (PositionComp*) getComponent("Position");
	connected = false;
	new_socket_rotation = socket_position->getRotation();
	old_socket_rotation = new_socket_rotation;
}

bool ConnectedComp::attach(PositionComp* mySocket, bool myHandleRotation)
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
			return true;
		}
	};

bool ConnectedComp::detach()
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

void ConnectedComp::update(double dt)
{
	if(connected)
	{
		
		Vector2 vector_from_socket = Vector2::ToVector2(radian_from_socket+socket_position->getRotation());
		Vector2 displacement = Vector2(vector_from_socket.x*distance, vector_from_socket.y*distance);

		connected_position->setPosition(socket_position->getPosition().x + displacement.x,
										socket_position->getPosition().y + displacement.y);
		if(handle_rotation)
		{
			new_socket_rotation = socket_position->getRotation();

			float new_connected_rotation = connected_position->getRotation() + (new_socket_rotation-old_socket_rotation);
			connected_position->setRotation(new_connected_rotation);

			old_socket_rotation = new_socket_rotation;
		}
	}
}