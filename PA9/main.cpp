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

	//event handler
	sf::Event event;

	//player object
	Player player(width/2,height/2);

	Projectile projectile;

	//timer in upper right corner
	sf::Font font;
	//font.loadFromFile("Tuffy.ttf");

	if (!font.loadFromFile("Tuffy.otf")){
		cout << "ERROR";
	}

	//projectile
	sf::RectangleShape bullet(sf::Vector2f(2, 2));
	bullet.setFillColor(sf::Color(255, 255, 255));

	//game loop
	while (window.isOpen()) {

		//process all the events
		while (window.pollEvent(event)) {
			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !T.getSec()) {
			T.setStart();
		}

		if (T.getStart()) {
			T.countdown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
			bullet.setPosition((projectile.getX()), (projectile.getY()));
			projectile.setLocation((player.getX()), (player.getY()), player.getRotation());
		}

		//update player coordinates
		player.updatePosition();
		player.updateSprite();
		projectile.updateLocation();
		bullet.setPosition(projectile.getX(), projectile.getY());
		bullet.setRotation(360 - player.getRotationDegrees());

		//Render
		window.clear();
		T.drawTimer(&window);
		window.draw(player.getSprite());
		if (projectile.isActivated())
			window.draw(bullet);
		window.display();
	}

	return 0;
}