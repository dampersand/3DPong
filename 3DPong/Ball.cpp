#include "Ball.h"
#include <iostream>

Ball::Ball(float screenX, float screenY, float r, float s, Border * b)
{
	minRadius = r * s;
	maxRadius = r;
	position.x = screenX/2 - maxRadius;
	position.y = screenY/2 - maxRadius;
	velocity.x = 100;
	velocity.y = 80;
	circle.setRadius(maxRadius);
	circle.setPosition(position);
	circle.setFillColor(sf::Color(255,255,0, 160));
	border = b;
	rzRatio = (maxRadius - minRadius) / (border->courtLength); //ratio of delta r to delta z - if you know delZ, you can determine delR.
}

bool Ball::inAICourt()
{
	if (border->z < 0)
		return true;
	else
		return false;
}

bool Ball::inPlayerCourt()
{
	if (border->z > border->courtLength)
		return true;
	else
		return false;
}

void Ball::moveBall(sf::Time updateTime)
{
	sf::Vector2f discrepancy; //change in position based on velocity
	sf::Vector2f oldCenter;
	sf::Vector2f newLocation;
	sf::Vector2f oldLength; //temp variables to make math easier, corresponds to half-length of playing field
	sf::Vector2f newLength;

	float newRadius; //will change size of circle
	float zee = border->z; //easier than actually working with pointers.
	float oldRadius; //temp variable to keep the old radius after changing it.


/////////////////////////////////////////////////////////
	//Change radius due to z velocity
	newRadius = rzRatio * zee + minRadius;	//linear formula of radius change wrt z
	oldRadius = circle.getRadius();			//going to fuck with the radius, save the change in deltaR

	circle.setRadius(newRadius);

/////////////////////////////////////////////////////////
	//Set up repositionings
	oldCenter.x = position.x + oldRadius; //set up reposition due to perspective
	oldCenter.y = position.y + oldRadius;

	//Okay.  Get ready.
	//oldcenter - border->maxSize.x/2 = the old location.
	newLength.x = border->maxSize.x/2 - border->position.x;
	newLength.y = border->maxSize.y/2 - border->position.y;
	oldLength.x = newLength.x - border->discrepancy.x/2;
	oldLength.y = newLength.y - border->discrepancy.y/2;
	//law of ratios gives us the new center.

	newLocation.x = ((oldCenter.x - border->maxSize.x/2) * newLength.x) / oldLength.x;
	newLocation.y = ((oldCenter.y - border->maxSize.y/2) * newLength.y) / oldLength.y;

	if ((velocity.y < 0) && touchingTopWall()) //set up reposition due to velocity
		velocity.y *= -1;
	if ((velocity.x > 0) && touchingRightWall())
		velocity.x *= -1;
	if ((velocity.y > 0) && touchingBottomWall())
		velocity.y *= -1;
	if ((velocity.x < 0) && touchingLeftWall())
		velocity.x *= -1;

	//set up velocity change due to scale change using law of ratios
	velocity.x = (velocity.x * newLength.x) / oldLength.x;
	velocity.y = (velocity.y * newLength.y) / oldLength.y;

	discrepancy.x = velocity.x * updateTime.asSeconds();
	discrepancy.y = velocity.y * updateTime.asSeconds();



	position.x += (newRadius - oldRadius);									//reposition due to radius change
	position.y += -(newRadius - oldRadius);										//negative due to absurd programming notation of up being negative
	position.x += (newLocation.x - (oldCenter.x - border->maxSize.x/2));		//reposition due to perspective
	position.y += (newLocation.y - (oldCenter.y - border->maxSize.y/2));		//negative due to absurd programming notation of up being negative
	position.x += discrepancy.x;												//reposition due to velocity
	position.y += discrepancy.y;
	circle.setPosition(position);

	center.x = position.x + circle.getRadius();
	center.y = position.y + circle.getRadius();

}

void Ball::changeVelocity()
{
}

bool Ball::touchingTopWall()
{
	if(position.y - 6 < border->position.y)
		return true;
	else
		return false;
}

bool Ball::touchingBottomWall()
{
	if(position.y + 2*circle.getRadius() + 6 > border->position.y + border->size.y)
		return true;
	else
		return false;
}

bool Ball::touchingLeftWall()
{
	if(position.x < border->position.x)
		return true;
	else
		return false;
}

bool Ball::touchingRightWall()
{
	if(position.x + 2*circle.getRadius() + 6 > border->position.x + border->size.x)
		return true;
	else
		return false;
}