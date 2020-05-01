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

	Score score;
	score.readScores();

	int minute = 0, second = 0;

	bool timerStart = false;
	time_t start;

	//create window
	sf::RenderWindow window(sf::VideoMode(width, height), "Azteroidz");
	window.setFramerateLimit(50);

	//event handler
	sf::Event event;

	//player object
	Player player(width/2,height/2);
	//projectile object
	Projectile projectile(width/2,height/2);
	//timer object
	Timer T;
	//stats object
	Stats stats;

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

		while (window.pollEvent(event)) {
			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (T.getStart()) {
			T.countdown();
		}

		if (!T.isTimeOut()) {
			//movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();

			//shooting
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) projectile.setLocation(player.getX(), player.getY(), player.getVelX(), player.getVelY(), player.getRotation());

			//update player coordinates
			player.updatePosition();
			player.updateSprite();
			projectile.updateLocation();
			projectile.updateSprite();
			stats.updateStats(&player);


			//Render
			window.clear();
			T.drawTimer(&window);
			stats.drawStats(&window);
			window.draw(player.getSprite());
			projectile.drawBullet(&window);
			window.display();
		}
		//once timer has run out
		else {
			//render
			window.clear();
			score.drawScores(&window, font);
			window.display();
		}
	}

	return 0;
}
