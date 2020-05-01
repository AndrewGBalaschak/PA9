/*
Programmer: Andrew Balaschak, Svetoslav Dimitrov, Seri Nakamura, Garett Pascual-Folster
Class: CPTS 122, Spring 2020; Lab Section 14
Programming Assignment:
Date:
Description:
*/

#include <iostream>
#include "header.h"
using namespace std;

int main() {
	int minute = 0, second = 0;

	Timer T;

	//create window
	sf::RenderWindow window(sf::VideoMode(width, height), "Azteroidz");
	window.setFramerateLimit(50);

	//event handler maybe?
	sf::Event event;

	//player object
	Player player(width/2, height/2);

	//game loop
	while (window.isOpen()) {

		//process all the events
		while (window.pollEvent(event)) {
			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !T.getStart())
			T.setStart();

		if (T.getStart()) {
			T.countdown();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();
		}

		//update player coordinates
		player.updateSprite();

		//Render
		window.clear();
		T.drawTimer(&window);
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}
