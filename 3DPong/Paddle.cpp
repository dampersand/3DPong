#include "Paddle.h"


AIPaddle::AIPaddle(float screenX, float screenY, float Velocity, int length, int height, float scale)
{
	size.x = length * scale;
	size.y = height * scale;
	position.x= screenX/2 - (size.x/2);
	position.y = screenY/2 - (size.y/2);
	maxVelocity = Velocity;
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(sf::Color(255,1,1));
}

void AIPaddle::movePaddle(float objectiveX, float objectiveY)
{
	float delX = objectiveX - position.x;
	float delY = objectiveY - position.y;
	position.x += delX*maxVelocity;
	position.y += delY*maxVelocity;
	rect.setPosition(position);
}
