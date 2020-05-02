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

	//objects list
	vector<MovingObject *> objs;
	Player player(width/2, height/2);
	objs.push_back(&player);

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

		//when the timer still has time left
		if (!T.isTimeOut()) {
			//movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();

			//shooting
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
				objs.push_back(new Projectile(player.getX(), player.getY(), player.getRotation()));

			//update player coordinates
			for (int i = 0; i < objs.size(); i++) {
				cout << "Update " << i;
				objs[i]->updatePosition();
				if (!objs[i]->getActive()) {
					delete objs[i];
					objs.erase(objs.begin() + i);
				}
			}

			stats.updateStats(&player);


			//Render
			window.clear();
			T.drawTimer(&window);
			stats.drawStats(&window);
			for (int i = 0; i < objs.size(); i++)
				objs[i]->draw(&window);
			window.display();
		}
		//once timer has run out
		else {

			score.writeScores();

			//render
			window.clear();
			score.drawScores(&window, font);
			window.display();
		}
	}

	return 0;
}
