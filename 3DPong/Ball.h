#ifndef _BALL_H
#define _BALL_H

#include "Borders.h"
#include <SFML/Graphics.hpp>

class Ball
{
	private:
		float minRadius;
		float maxRadius;
		float decayRate;
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Vector2f lastBounce;
		Border* border;

	public:
		Ball::Ball(float screenX, float screenY, float r, float s, float decay, Border * border);

		sf::Vector2f center;
		sf::CircleShape circle;
		bool inAICourt();
		bool inPlayerCourt();
		bool inCurveZone(sf::Time currentTime);
		
		void moveBall(sf::Time updateTime);
		void changeVelocity(sf::Vector2f paddleCenter);
		void addCurve(sf::Vector2f paddleCenter);
		void resetBall(float screenX, float screenY);
		bool touchingTopWall();
		bool touchingBottomWall();
		bool touchingLeftWall();
		bool touchingRightWall();

		bool touchingPaddle(sf::RectangleShape rect);
};

#endif //_BALL_H guard word