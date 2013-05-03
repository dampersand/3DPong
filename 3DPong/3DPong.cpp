#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "Paddle.h"
#include "Borders.h"
#include "Ball.h"
#include "Background.h"


#define AI_SCALE 0.5f
#define PADDLE_LENGTH 120.0f
#define PADDLE_HEIGHT 90.0f
#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f
#define COURT_LENGTH 100.0f
#define BALL_RADIUS 50.0f
#define AI_MAX_SPEED 300.0f
#define REFRESH_RATE 0.01f //in seconds
#define DECAY_RATE 0.95f


int main()
{
	sf::RenderWindow mainWindow; //initiate the window		
	mainWindow.create(sf::VideoMode(800,600), "3D Pong", sf::Style::Default); //create the window

	Background background(SCREEN_WIDTH,SCREEN_HEIGHT,AI_SCALE); //create background
	Border border(SCREEN_WIDTH, SCREEN_HEIGHT, AI_SCALE, COURT_LENGTH); //initialize moving borders
	Ball ball(SCREEN_WIDTH, SCREEN_HEIGHT, BALL_RADIUS, AI_SCALE, DECAY_RATE, &border);
	AIPaddle opponent(SCREEN_WIDTH, SCREEN_HEIGHT, AI_MAX_SPEED, PADDLE_LENGTH, PADDLE_HEIGHT, AI_SCALE, &border, &background); // initialize opponent paddle
	playerPaddle paddle(SCREEN_WIDTH, SCREEN_HEIGHT, PADDLE_LENGTH, PADDLE_HEIGHT); //initialize player paddle

	int flashFlag = 0; //using threads blows
	sf::Event ev; //event checker
	sf::Clock clock, updateClock; //clocks
	sf::Time bounceTime, currentTime, updateTime; //time between bounces, current time since last bounce, and time between updates.

	bool gameOn = false;


	while (mainWindow.isOpen()) // main window loop
	{
/////////////////////////////////////////////////
		//redraw everything
		mainWindow.clear(sf::Color::White);
		mainWindow.draw(background.maxRect);
		mainWindow.draw(background.threeQuartRect);
		mainWindow.draw(background.halfRect);
		mainWindow.draw(background.quartRect);
		mainWindow.draw(background.minRect);
		mainWindow.draw(border.rect);
		mainWindow.draw(opponent.rect);
		mainWindow.draw(ball.circle);
		mainWindow.draw(paddle.rect);
		mainWindow.display();
////////////////////////////////////////////////
		paddle.movePaddle(sf::Mouse::getPosition(mainWindow)); // player always controls paddle

		if (gameOn)
		{
			currentTime = clock.getElapsedTime(); //update times
			updateTime = updateClock.getElapsedTime();

			if ((ball.inAICourt() || ball.inPlayerCourt()) && currentTime.asSeconds() > 1.5*REFRESH_RATE) //if it's time to bounce, and give the ball time to get out of court
			{
				if ( (ball.inAICourt() && ball.touchingPaddle(opponent.rect)) || (ball.inPlayerCourt() && ball.touchingPaddle(paddle.rect)) )
				{
					bounceTime = border.reverseDirection(bounceTime, REFRESH_RATE); //bounce
					clock.restart();
					if (ball.inAICourt())
					{
						ball.changeVelocity(opponent.center);
						flashFlag = 1;
					}
					else if (ball.inPlayerCourt())
					{
						ball.changeVelocity(paddle.center);
						flashFlag = 2;
					}
				}
				else
				{
					ball.resetBall(SCREEN_WIDTH, SCREEN_HEIGHT);
					opponent.resetPaddle(SCREEN_WIDTH, SCREEN_HEIGHT);
					paddle.resetPaddle(SCREEN_WIDTH, SCREEN_HEIGHT);
					border.resetBorder();
					gameOn = false;
				}

			} //END bounce check

			if (updateTime.asSeconds() >= REFRESH_RATE) //if it's time to update (once every ten milliseconds)
			{
				if (ball.inCurveZone(currentTime)) //if the ball can be curved, curve it.
					ball.addCurve(paddle.center);

				if (flashFlag == 1)
					opponent.flashPaddle(currentTime);
				else if (flashFlag == 2)
					paddle.flashPaddle(currentTime);


				border.moveBorder(updateTime); //update the border's location
				ball.moveBall(updateTime); //update the ball's location
				opponent.movePaddle(ball.center.x, ball.center.y, updateTime); //move the opponent's paddle
				updateTime.Zero;
				updateClock.restart();
			} //END update check
		}//END game "on" check

		else if (!gameOn)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ball.touchingPaddle(paddle.rect))
				{
					clock.restart();
					updateClock.restart();
					bounceTime = sf::seconds(1.0f);
					bounceTime = border.reverseDirection(bounceTime, REFRESH_RATE);
					ball.changeVelocity(paddle.center);
					gameOn = true;
				}
			}


		while(mainWindow.pollEvent(ev)) //event loop
		{
			if (ev.type == sf::Event::Closed) //if someone has closed the window
				mainWindow.close();
			
		}//END Event Loop
	}//END main loop
    return 0;
}