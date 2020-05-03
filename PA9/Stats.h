#ifndef STATS_H
#define STATS_H

#include "Player.h"

class Stats {
private:
	int fuel, score;
	sf::Text* fuelNum, * scoreNum, * fuelText, * scoreText;
	sf::Font font;
public:
	Stats() {
		fuel = 500;
		score = 0;
		if (!font.loadFromFile("Tuffy.otf")) std::cout << "ERROR";

		fuelNum = new sf::Text(std::to_string(0), font);
		scoreNum = new sf::Text(std::to_string(0), font);
		fuelText = new sf::Text("Fuel: ", font);
		scoreText = new sf::Text("Score: ", font);

		fuelText->setPosition(WIDTH - 80, 50);
		fuelText->setCharacterSize(15);
		scoreText->setPosition(WIDTH - 80, 70);
		scoreText->setCharacterSize(15);
		fuelNum->setPosition(WIDTH - 30, 50);
		fuelNum->setCharacterSize(15);
		scoreNum->setPosition(WIDTH - 30, 70);
		scoreNum->setCharacterSize(15);
	}
	void updateStats(Player* p) {
		fuel = p->getFuel();
		score = p->getScore();
		if (fuel >= 0) {
			fuelNum->setString(std::to_string(fuel));
		}
		scoreNum->setString(std::to_string(score));
	}
	void drawStats(RenderWindow* win) {
		win->draw(*fuelText);
		win->draw(*scoreText);
		win->draw(*fuelNum);
		win->draw(*scoreNum);
	}

};



#endif
