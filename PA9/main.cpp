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
	int minute = 0, second = 0;

	bool timerStart = false;

	time_t start;

	Timer T;

	//create window
	sf::RenderWindow window(sf::VideoMode(width, height), "Azteroidz");
	window.setFramerateLimit(50);

	//event handler maybe?
	sf::Event event;

	//player object
	Player player(400, 300);

	//timer in upper right corner
	sf::Font font;
	//font.loadFromFile("Tuffy.ttf");

	if (!font.loadFromFile("Tuffy.otf")){
		cout << "ERROR";
	}

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

		//process all the events
		while (window.pollEvent(event)) {
			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			time(&start);
			T.setStart(start);
			timerStart = true;
		}

		if (timerStart) { // delay needs to be tested
			timerStart = T.countdown();
			minute = T.getMin();
			min.setString(std::to_string(minute));
			second = T.getSec();
			sec.setString(std::to_string(second));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();

		//update player coordinates
		player.updatePosition();
		player.updateSprite();

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
		window.draw(player.getSprite());
		window.display();
	}

	return 0;
}
