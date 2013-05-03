#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background
{
public:
	Background::Background(float screenX, float screenY, float scale);
	sf::RectangleShape maxRect;
	sf::RectangleShape threeQuartRect;
	sf::RectangleShape halfRect;
	sf::RectangleShape quartRect;
	sf::RectangleShape minRect;

	void setUpRectangle(float screenX, float screenY, float scale, float rectScale, sf::RectangleShape &rect);
};


#endif //end of _BACKGROUND_H guard word