#include "ConnectedComp.h"


// W/ socket
ConnectedComp::ConnectedComp(float myRadianFromSocket, float myDistance, Entity* myParent) 
	: Component("Connected",myParent), distance(myDistance),radian_from_socket(myRadianFromSocket)
{
	connected_position = (PositionComp*) getComponent("Position");
	connected = false;
}


void ConnectedComp::update(float dt)
{
	if(connected)
	{
		Vector2 vector_from_socket = Vector2::ToVector2(radian_from_socket+socket_position->getRotation());
		Vector2 displacement = Vector2(vector_from_socket.x*distance, vector_from_socket.y*distance);

		connected_position->setPosition(socket_position->getPosition().x + displacement.x,
										socket_position->getPosition().y + displacement.y);
		if(handle_rotation)
			connected_position->setRotation(socket_position->getRotation());
		
	}
}