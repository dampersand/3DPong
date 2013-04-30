#ifndef _PADDLE_H
#define _PADDLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Paddle
{
protected:
	sf::Vector2f size;
public:
	sf::Vector2f position;
	sf::RectangleShape rect;

};

class AIPaddle: public Paddle
{
private:
	float maxVelocity;
public:
	AIPaddle::AIPaddle(float screenX, float screenY, float Velocity, int length, int height, float scale); //constructor
	void movePaddle(float objectiveX, float objectiveY);
};


#endif //_PADDLE_H guard word