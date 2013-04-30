#include "Borders.h"

Border::Border(float screenX, float screenY, float s, float cL)
{
	z = 0;
	size.x = screenX;
	size.y = screenY;
	maxSize.x = screenX;
	maxSize.y = screenY;
	direction = 0;
	rect.setPosition(0,0);
	position = rect.getPosition();
	rect.setSize(size);
	rect.setOutlineThickness(-2);
	rect.setOutlineColor(sf::Color::Green);
	rect.setFillColor(sf::Color(0,0,0,0));
	velocity.z = 0;
	velocity.x = 0;
	velocity.y = 0;
	scale = s;
	courtLength = cL;
	minSize.x = s*screenX;
	minSize.y = s*screenY;
}

sf::Time Border::reverseDirection(sf::Time bounceTime)
{
	if (direction == -1)
		direction = 1;
	else
		direction = -1;

	bounceTime = bounceTime * 0.95f;
	velocity.z = courtLength / bounceTime.asSeconds();
	velocity.x = (maxSize.x - minSize.x) / bounceTime.asSeconds();
	velocity.y = (maxSize.y - minSize.y) / bounceTime.asSeconds();
	return bounceTime;
}

void Border::moveBorder(sf::Time updateTime)
{
	sf::Vector3f discrepancy;

	discrepancy.z= -direction * velocity.z * updateTime.asSeconds(); //calculate the distance the border should travel on the z axis; negative because z is backwards
	discrepancy.x = direction * velocity.x * updateTime.asSeconds(); //calculate the size change on the x axis
	discrepancy.y = direction * velocity.y * updateTime.asSeconds(); //calculate the size change on the y axis

	z += discrepancy.z; //add the discrepancy into each direction
	size.x += discrepancy.x;
	size.y += discrepancy.y;

	rect.setSize(size);
	
	position.x += -discrepancy.x / 2; //negatives included because when the discrepancy shrinks, the location of the rectangle technically grows.
	position.y += -discrepancy.y / 2; //stupid programming notation.  Why can't we be scientific instead?

	rect.setPosition(position);
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