#include "Ball.h"

Ball::Ball(float screenX, float screenY, float r, float s, float decay, Border * b)
{
	minRadius = r * s;
	maxRadius = r;
	decayRate = decay;
	lastBounce.x = screenX/2;
	lastBounce.y = screenY/2;
	position.x = screenX/2 - maxRadius;
	position.y = screenY/2 - maxRadius;
	velocity.x = 0;
	velocity.y = 0;
	acceleration.x = 0;
	acceleration.y = 0;
	circle.setRadius(maxRadius);
	circle.setPosition(position);
	circle.setFillColor(sf::Color(255,255,0));
	border = b;
}

bool Ball::inAICourt()
{
	if (border->z <= 0)
		return true;
	else
		return false;
}

bool Ball::inPlayerCourt()
{
	if (border->z >= border->courtLength)
		return true;
	else
		return false;
}

bool Ball::inCurveZone(sf::Time currentTime)
{
	if (currentTime.asSeconds() < 0.08 && border->direction == -1)
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
	newRadius = (((maxRadius - minRadius) / (border->courtLength))   *   zee) + minRadius;	//linear formula of radius change wrt z
	oldRadius = circle.getRadius();			//going to fuck with the radius, save the change in deltaR

	circle.setRadius(newRadius);

/////////////////////////////////////////////////////////
	//Set up repositionings
/////////////////////////////////////////////////////////
	//set up reposition due to perspective
	oldCenter.x = position.x + oldRadius;
	oldCenter.y = position.y + oldRadius;

	//oldcenter - border->maxSize.x/2 = the old location.
	newLength.x = border->maxSize.x/2 - border->position.x;
	newLength.y = border->maxSize.y/2 - border->position.y;
	oldLength.x = newLength.x - border->discrepancy.x/2;
	oldLength.y = newLength.y - border->discrepancy.y/2;
	//law of ratios gives us the new center.

	newLocation.x = ((oldCenter.x - border->maxSize.x/2) * newLength.x) / oldLength.x;
	newLocation.y = ((oldCenter.y - border->maxSize.y/2) * newLength.y) / oldLength.y;


	//set up velocity change due to scale change using law of ratios
	velocity.x = (velocity.x * newLength.x) / oldLength.x;
	velocity.y = (velocity.y * newLength.y) / oldLength.y;

	//set up acceleration change due to scale change using law of ratios
	acceleration.x = (acceleration.x * newLength.x) / oldLength.x;
	acceleration.y = (acceleration.y * newLength.y) / oldLength.y;

	//set up velocity change due to acceleration
	velocity.x += acceleration.x * updateTime.asSeconds();
	velocity.y += acceleration.y * updateTime.asSeconds();

	//decay acceleration to simulate Magnus effect
	acceleration.x *= decayRate;
	acceleration.y *= decayRate;


	//set up reposition due to velocity
	if ((velocity.y < 0) && touchingTopWall())
		velocity.y *= -1;
	if ((velocity.x > 0) && touchingRightWall())
		velocity.x *= -1;
	if ((velocity.y > 0) && touchingBottomWall())
		velocity.y *= -1;
	if ((velocity.x < 0) && touchingLeftWall())
		velocity.x *= -1;

	//calculate what reposition should be due to velocity
	discrepancy.x = velocity.x * updateTime.asSeconds();
	discrepancy.y = velocity.y * updateTime.asSeconds();



	position.x += -(newRadius - oldRadius);										//reposition due to radius change
	position.y += -(newRadius - oldRadius);										//negative due to absurd programming notation of up being negative
	position.x += (newLocation.x - (oldCenter.x - border->maxSize.x/2));		//reposition due to perspective
	position.y += (newLocation.y - (oldCenter.y - border->maxSize.y/2));		//negative due to absurd programming notation of up being negative
	position.x += discrepancy.x;												//reposition due to velocity
	position.y += discrepancy.y;
	circle.setPosition(position);

	center.x = position.x + circle.getRadius();
	center.y = position.y + circle.getRadius();

}

void Ball::changeVelocity(sf::Vector2f paddleCenter)
{
	velocity.x += (center.x - paddleCenter.x)/5;
	velocity.y += (center.y - paddleCenter.y)/5;

	lastBounce.x = paddleCenter.x; //record where the paddle was when it hit you.
	lastBounce.y = paddleCenter.y;
}

void Ball::addCurve(sf::Vector2f paddleCenter)
{
	acceleration.x += 12*(lastBounce.x - paddleCenter.x);
	acceleration.y += 14*(lastBounce.y - paddleCenter.y);
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

bool Ball::touchingPaddle(sf::RectangleShape rect)
{
	sf::Rect<float> ballRect;
	const sf::Rect<float> paddleRect = rect.getGlobalBounds();
	ballRect = circle.getGlobalBounds();

	if (ballRect.intersects(paddleRect))
		return true;
	else
		return false;
}

void Ball::resetBall(float screenX, float screenY)
{
	position.x = screenX/2 - maxRadius;
	position.y = screenY/2 - maxRadius;
	velocity.x = 0;
	velocity.y = 0;
	circle.setRadius(maxRadius);
	circle.setPosition(position);
	lastBounce.x = screenX/2;
	lastBounce.y = screenY/2;
}
