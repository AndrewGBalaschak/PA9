/*
Programmer: Andrew Balaschak, Svetoslav Dimitrov, Seri Nakamura, Garett 
Class: CPTS 122, Spring 2020; Lab Section 14
Programming Assignment:
Date:
Description:
*/

#include <iostream>
#include "header.h"
using namespace std;

int main() {
	int width = 800, height = 600;

	//create window
	sf::RenderWindow window(sf::VideoMode(width, height), "Azteroidz");

	//event handler maybe?
	sf::Event event;

	//player object
	Player player;

	//black rectangle for player
	//sf::RectangleShape playerSprite(sf::Vector2f(50, 50));
	sf::CircleShape playerSprite(50, 3);
	playerSprite.setFillColor(sf::Color(255, 255, 255));
	playerSprite.setPosition(player.getX(), player.getY());
	playerSprite.setOrigin(50, 50);

	//game loop
	while (window.isOpen()) {
		//process all the events
		while (window.pollEvent(event)) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();

			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}


		//update player coordinates
		player.updatePosition();
		playerSprite.setPosition(player.getX(), player.getY());
		playerSprite.setRotation(360 - player.getRotationDegrees() - 30);

		//Render
		window.clear();
		window.draw(playerSprite);
		window.display();
	}

	return 0;
}