#include "Background.h"

Background::Background(float screenX, float screenY, float scale)
{
	//set the closest rectangle
	setUpRectangle(screenX,screenY,scale,0.001,maxRect); //include fudge-factor rectScale so we actually SEE the line

	//set the 3/4 size rectangle
	setUpRectangle(screenX,screenY,scale,0.25,threeQuartRect);

	//set up the half size rectangle
	setUpRectangle(screenX,screenY,scale,0.5,halfRect);

	//set up quarter size rectangle
	setUpRectangle(screenX,screenY,scale,0.75,quartRect);

	//set up minimum rectangle
	setUpRectangle(screenX,screenY,scale,1,minRect);
	minRect.setFillColor(sf::Color::White);

}

void Background::setUpRectangle(float screenX, float screenY, float scale, float rectScale, sf::RectangleShape &rect)
{
	sf::Vector2f size;
	sf::Vector2f position; //variables that will change size and position for each rectangle
	sf::Vector2f difference;
	difference.x = screenX - (screenX * scale); //difference in length between max and min rectangles
	difference.y = screenY - (screenY * scale);

	size.x = screenX - (rectScale*difference.x);
	size.y = screenY - (rectScale*difference.y);
	position.x = (rectScale*difference.x)/2;
	position.y = (rectScale*difference.y)/2;
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(sf::Color(128,128,128));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
}