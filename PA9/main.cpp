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

	//black rectangle for player
	sf::RectangleShape player(sf::Vector2f(50, 50));
	player.setFillColor(sf::Color(255, 255, 255));
	player.setPosition(width/2, height/2);

	//game loop
	while (window.isOpen()) {

		//get player coordinates
		sf::Vector2f pPos = player.getPosition();

		//process all the events
		while (window.pollEvent(event)) {

			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//Render
		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}