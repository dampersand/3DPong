#ifndef _BALL_H
#define _BALL_H

#include "Borders.h"
#include <SFML/Graphics.hpp>

class Ball
{
	private:
		float minRadius;
		float maxRadius;
		sf::Vector2f position;
		sf::Vector2f velocity;
		float rzRatio;
		Border* border;

	public:
		Ball::Ball(float screenX, float screenY, float r, float s, Border * border);

		sf::Vector2f center;
		sf::CircleShape circle;
		bool inAICourt();
		bool inPlayerCourt();
		
		void moveBall(sf::Time updateTime);
		void changeVelocity(sf::Vector2f paddleCenter);
		void resetBall(float screenX, float screenY);
		bool touchingTopWall();
		bool touchingBottomWall();
		bool touchingLeftWall();
		bool touchingRightWall();

		bool touchingPaddle(sf::RectangleShape rect);
};

#endif //_BALL_H guard word