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
	int width = 800, height = 600;

	sf::Clock clock;
	double timer = 0, delay = 0.05;
	
	bool timerStart = false;

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
	
	//timer in upper right corner
	sf::Font font;
	font.loadFromFile("Tuffy.ttf");

	sf::Text min("", font);
	min.setString(std::to_string(T.getMin()));
	min.setPosition(width - 80, 7);
	min.setCharacterSize(30);
	sf::Text colon("", font);
	colon.setString(":");
	colon.setPosition(width - 60, 5);
	colon.setCharacterSize(30);
	sf::Text sec("", font);
	sec.setString(std::to_string(T.getSec()));
	sec.setPosition(width - 45, 7);
	sec.setCharacterSize(30);
	sf::Text zero("", font);
	zero.setString("0");
	zero.setPosition(width - 45, 7);
	zero.setCharacterSize(30);

	//game loop
	while (window.isOpen()) {
		/*
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		*/

		//process all the events
		while (window.pollEvent(event)) {
			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		if (timerStart) { // delay needs to be tested
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();
		}

		//update player coordinates
		player.updatePosition();
		playerSprite.setPosition(player.getX(), player.getY());
		playerSprite.setRotation(360 - player.getRotationDegrees() - 30);
		
		//timer
		if (timerStart) {
			timerStart = T.countdown();
			minute = T.getMin();
			min.setString(std::to_string(minute));
			second = T.getSec();
			sec.setString(std::to_string(second));
		}

		

		//Render
		window.clear();
		if (second < 10) {
			window.draw(zero);
			sec.setPosition(width - 28, 7);
		}
		else {
			sec.setPosition(width - 45, 7);
		}
		window.draw(min);
		window.draw(colon);
		window.draw(sec);
		window.display();
		window.draw(playerSprite);
		window.display();
	}

	return 0;
}
