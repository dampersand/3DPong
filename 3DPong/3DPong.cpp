#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Borders.h"
//#include <iostream> for testing purposes

#define AI_SCALE 0.5
#define PADDLE_LENGTH 90
#define PADDLE_WIDTH 75
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define COURT_LENGTH 100

int main()
{
	sf::RenderWindow mainWindow; //initiate the window		
	mainWindow.create(sf::VideoMode(800,600), "3D Pong", sf::Style::Default); //create the window

	AIPaddle opponent(SCREEN_WIDTH, SCREEN_HEIGHT, 0.005, 100, 50, AI_SCALE); // initialize opponent paddle
	Border border(SCREEN_WIDTH, SCREEN_HEIGHT, AI_SCALE, COURT_LENGTH);
	sf::Event ev; //event checker
	sf::Clock clock; //clock
	sf::Time bounceTime, currentTime, updateTime; //time between bounces, current time, and time between updates.

	bool gameOn = false;


	while (mainWindow.isOpen()) // main window loop
	{
/////////////////////////////////////////////////
		//redraw everything
		mainWindow.clear(sf::Color::White); 
		mainWindow.draw(border.rect);
		mainWindow.draw(opponent.rect);
		mainWindow.display();
////////////////////////////////////////////////

		if (gameOn)
			{
				currentTime = clock.getElapsedTime(); //update times
				updateTime = clock.getElapsedTime();

				if (bounceTime.asSeconds() <= currentTime.asSeconds()) //if it's time to bounce
				{
					bounceTime = border.reverseDirection(bounceTime); //bounce
					clock.restart();
				}

				if (updateTime.asSeconds() >= 0.01f) //if it's time to update (once every ten milliseconds)
				{
					border.moveBorder(updateTime); //update the border's location
					updateTime = sf::seconds(0);
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
					bounceTime = sf::seconds(2.0f);
					bounceTime = border.reverseDirection(bounceTime);
					gameOn = true;
				}
			}

			
		}//END Event Loop
	}//END main loop
    return 0;
}