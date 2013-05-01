#ifndef _BORDERS_H
#define _BORDERS_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Border //moving border to help player determine Z axis
{
protected:
	float z;						//z axis location; probably should have used a vector
	float direction;				//automated z-direction scalar
	sf::Vector2f minSize;			//vector for border size
	sf::Vector2f maxSize;			//vector for border size
	sf::Vector2f position;			//position of moving border
	sf::Vector3f velocity;			//changing speed of border
	float scale;					//help make various calculations
	float courtLength;				//length of ball court
	sf::Vector3f discrepancy;

public:
	Border::Border(float screenX, float screenY, float s, float cL);
	sf::Vector2f size;
	sf::RectangleShape rect;

	sf::Time reverseDirection(sf::Time bounceTime);
	void moveBorder(sf::Time updateTime);

	friend class Ball;
};



#endif //_BORDERS_H guard word