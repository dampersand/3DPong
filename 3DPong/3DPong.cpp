#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Borders.h"
#include "Ball.h"
#include <iostream>

#define AI_SCALE 0.5f
#define PADDLE_LENGTH 120.0f
#define PADDLE_HEIGHT 90.0f
#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f
#define COURT_LENGTH 100.0f
#define BALL_RADIUS 50.0f
#define AI_MAX_SPEED 100.0f

int main()
{
	sf::RenderWindow mainWindow; //initiate the window		
	mainWindow.create(sf::VideoMode(800,600), "3D Pong", sf::Style::Default); //create the window

	AIPaddle opponent(SCREEN_WIDTH, SCREEN_HEIGHT, AI_MAX_SPEED, PADDLE_LENGTH, PADDLE_HEIGHT, AI_SCALE); // initialize opponent paddle
	playerPaddle paddle(SCREEN_WIDTH, SCREEN_HEIGHT, PADDLE_LENGTH, PADDLE_HEIGHT); //initialize player paddle
	Border border(SCREEN_WIDTH, SCREEN_HEIGHT, AI_SCALE, COURT_LENGTH); //initialize moving borders
	Ball ball(SCREEN_WIDTH, SCREEN_HEIGHT, BALL_RADIUS, AI_SCALE, &border);


	sf::Event ev; //event checker
	sf::Clock clock, updateClock; //clocks
	sf::Time bounceTime, currentTime, updateTime; //time between bounces, current time, and time between updates.

	bool gameOn = false;


	while (mainWindow.isOpen()) // main window loop
	{
/////////////////////////////////////////////////
		//redraw everything
		mainWindow.clear(sf::Color::White); 
		mainWindow.draw(border.rect);
		mainWindow.draw(opponent.rect);
		mainWindow.draw(ball.circle);
		mainWindow.draw(paddle.rect);
		mainWindow.display();
////////////////////////////////////////////////

		if (gameOn)
			{
				currentTime = clock.getElapsedTime(); //update times
				updateTime = updateClock.getElapsedTime();

				if ((ball.inAICourt() || ball.inPlayerCourt()) && currentTime.asSeconds() > 0.1) //if it's time to bounce
				{
					if ( (ball.inAICourt() && ball.touchingPaddle(opponent.rect)) || (ball.inPlayerCourt() && ball.touchingPaddle(paddle.rect)) )
					{
						bounceTime = border.reverseDirection(bounceTime); //bounce
						if (ball.inAICourt())
							ball.changeVelocity(opponent.center);
						else if (ball.inPlayerCourt())
							ball.changeVelocity(paddle.center);
						clock.restart();
					}
					else
					{
						ball.resetBall(SCREEN_WIDTH, SCREEN_HEIGHT);
						opponent.resetPaddle(SCREEN_WIDTH, SCREEN_HEIGHT);
						border.resetBorder();
						gameOn = false;
					}

				}

				if (updateTime.asSeconds() >= 0.01f) //if it's time to update (once every ten milliseconds)
				{
					border.moveBorder(updateTime); //update the border's location
					ball.moveBall(updateTime);
					opponent.movePaddle(ball.center.x, ball.center.y, updateTime);
					paddle.movePaddle(sf::Mouse::getPosition(mainWindow));
					updateTime.Zero;
					updateClock.restart();
					//std::cout << ball.center.x <<" " << opponent.getCenter << std::endl;
				}
			}



		while(mainWindow.pollEvent(ev)) //event loop
		{
			if (ev.type == sf::Event::Closed) //if someone has closed the window
				mainWindow.close();

			if (!gameOn)
			{
				if (ev.type == sf::Event::MouseButtonPressed)
				{
					clock.restart();
					updateClock.restart();
					bounceTime = sf::seconds(2.0f);
					bounceTime = border.reverseDirection(bounceTime);
					gameOn = true;
				}
			}


			
		}//END Event Loop
	}//END main loop
    return 0;
}