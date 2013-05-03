#include "Paddle.h"
#include <cmath>

void Paddle::flashPaddle(sf::Time timeSinceBounce)
{
	sf::Color original = rect.getFillColor();
	if (timeSinceBounce.asMilliseconds() > 255)
		return;
	else
		rect.setFillColor(sf::Color(255-timeSinceBounce.asMilliseconds(), 0 + timeSinceBounce.asMilliseconds(), 0+timeSinceBounce.asMilliseconds(), original.a));

}


AIPaddle::AIPaddle(float screenX, float screenY, float Velocity, int length, int height, float scale, Border * b, Background *back)
{
	size.x = length * scale;
	size.y = height * scale;
	maxVelocity = Velocity;
	rect.setSize(size);
	rect.setFillColor(sf::Color(0,255,255));
	border = b;
	background = back;

	resetPaddle(screenX, screenY);
}

void AIPaddle::movePaddle(float objectiveX, float objectiveY, sf::Time updateTime)
{
	sf::Vector2i direction;
	sf::Vector2f boundaries = background->minRect.getPosition();
	sf::Vector2f boundSize = background->minRect.getSize();

	//if the ball was headed away from AI_Paddle, send AI_Paddle back to center instead.
	if (border->direction == 1)
	{
		objectiveX = border->maxSize.x/2;
		objectiveY = border->maxSize.y/2;
	}

	//detemine the direction the paddle has to move to hit the ball
	if (center.x >= objectiveX)
		direction.x = -1;
	else
		direction.x = 1;

	if (center.y >= objectiveY)
		direction.y = -1;
	else
		direction.y = 1;


	//determine the new position of the paddle
	if (abs(center.x - objectiveX) < (maxVelocity * updateTime.asSeconds())) //if you're within your stepsize, just go to the ball - don't overshoot.
		position.x += (objectiveX - center.x);
	else
		position.x += maxVelocity * updateTime.asSeconds() * direction.x; //otherwise, move as far as you can toward the ball.

	if (abs(center.y - objectiveY) < (maxVelocity * updateTime.asSeconds()))
		position.y += (objectiveY - center.y);
	else
		position.y += maxVelocity * updateTime.asSeconds() * direction.y;


	//if your move would put you out of bounds, simply go to the bounds.
	if (position.x < boundaries.x)
		position.x = boundaries.x;
	else if (position.x + size.x > boundaries.x + boundSize.x)
		position.x = boundaries.x + boundSize.x - size.x;

	if (position.y < boundaries.y)
		position.y = boundaries.y;
	else if (position.y + size.y > boundaries.y + boundSize.y)
		position.y = boundaries.y + boundSize.y - size.y;



	center.x = position.x + size.x/2; //update centers
	center.y = position.y + size.y/2;

	rect.setPosition(position); //confirm move and update location
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
	rect.setSize(size);
	rect.setFillColor(sf::Color(0,255,255,60));

	resetPaddle(screenX, screenY);
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
