#include "Borders.h"
#include <iostream>

Border::Border(float screenX, float screenY, float s, float cL)
{
	z = 0;
	sizeVector.x = screenX;
	sizeVector.y = screenY;
	direction = 0;
	rect.setPosition(0,0);
	position = rect.getPosition();
	rect.setSize(sizeVector);
	rect.setOutlineThickness(-2);
	rect.setOutlineColor(sf::Color::Green);
	rect.setFillColor(sf::Color(0,0,0,0));
	velocity = 0;
	scale = s;
	int const courtLength = cL;
}

sf::Time Border::reverseDirection(sf::Time bounceTime)
{
	if (direction == -1)
		direction = 1;
	else
		direction = -1;

	bounceTime = bounceTime * 0.9f;
	velocity = courtLength / bounceTime.asSeconds();
	return bounceTime;
}

void Border::moveBorder(sf::Time updateTime)
{
	//This needs to move the border first away, then toward the player.
	//This is done by resizing the sizeVector components and the position components.
	//This should also record and change the z position of the box.
}

bool Border::inAICourt()
{
	if (z >= courtLength)
		return true;
	else
		return false;
}

bool Border::inPlayerCourt()
{
	if (z <= 0)
		return true;
	else
		return false;
}