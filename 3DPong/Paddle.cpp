#include "Paddle.h"
#include <cmath>


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
	center.x = screenX/2;
	center.y = screenY/2;
}

void AIPaddle::movePaddle(float objectiveX, float objectiveY, sf::Time updateTime)
{
	sf::Vector2i direction; 

	if (center.x >= objectiveX) //detemine the direction the paddle has to move to hit the ball
		direction.x = -1;
	else
		direction.x = 1;

	if (center.y >= objectiveY)
		direction.y = -1;
	else
		direction.y = 1;


	if (abs(center.x - objectiveX) < (maxVelocity * updateTime.asSeconds())) //if you're within your stepsize, just go to the ball - don't overshoot.
		position.x += (objectiveX - center.x);
	else
		position.x += maxVelocity * updateTime.asSeconds() * direction.x; //otherwise, move as far as you can toward the ball.

	if (abs(center.y - objectiveY) < (maxVelocity * updateTime.asSeconds()))
		position.y += (objectiveY - center.y);
	else
		position.y += maxVelocity * updateTime.asSeconds() * direction.y;

	center.x = position.x + size.x/2; //update centers
	center.y = position.y + size.y/2;

	rect.setPosition(position); //move the paddle
}

void AIPaddle::resetPaddle(float screenX, float screenY)
{
	position.x= screenX/2 - (size.x/2);
	position.y = screenY/2 - (size.y/2);
	center.x = screenX/2;
	center.y = screenY/2;
	rect.setPosition(position);
}



playerPaddle::playerPaddle(float screenX, float screenY, int length, int height)
{
	size.x = length;
	size.y = height;
	position.x = screenX/2 - (size.x/2);
	position.y = screenY/2 - (size.y/2);
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(sf::Color(0,255,255,60));
	center.x = screenX/2;
	center.y = screenY/2;
}

void playerPaddle::movePaddle(sf::Vector2i mouseLocation)
{
	position.x = mouseLocation.x - size.x/2;
	position.y = mouseLocation.y - size.y/2;
	rect.setPosition(position);
	center.x = position.x + size.x/2;
	center.y = position.y + size.y/2;
}

void playerPaddle::resetPaddle(float screenX, float screenY)
{
	position.x= screenX/2 - (size.x/2);
	position.y = screenY/2 - (size.y/2);
	center.x = screenX/2;
	center.y = screenY/2;
	rect.setPosition(position);
}
