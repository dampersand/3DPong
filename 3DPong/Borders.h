#ifndef _BORDERS_H
#define _BORDERS_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Border
{
private:
	float z;
	float direction;
	sf::Vector2f sizeVector;
	sf::Vector2f position;
	float velocity;
	float scale;
	float courtLength;
public:
	Border::Border(float screenX, float screenY, float s, float cL);
	sf::RectangleShape rect;
	void moveBorder(sf::Time updateTime);
	sf::Time reverseDirection(sf::Time bounceTime);
	bool inAICourt();
	bool inPlayerCourt();
};



#endif //_BORDERS_H guard word