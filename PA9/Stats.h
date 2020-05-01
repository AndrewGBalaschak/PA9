#ifndef STATS_H
#define STATS_H

class Stats {
private:
	int fuel, score;
	sf::Text* fuelNum, * scoreNum, *fuelText, *scoreText;
	sf::Font font;
public:
	Stats(){
		fuel = 500;
		score = 0;
		if (!font.loadFromFile("Tuffy.otf")) cout << "ERROR";

		fuelNum = new sf::Text(to_string(0), font);
		scoreNum = new sf::Text(to_string(0), font);
		fuelText = new sf::Text("Fuel: ", font);
		scoreText = new sf::Text("Score: ", font);

		fuelText->setPosition(width - 80, 20);
		fuelText->setCharacterSize(30);
		scoreText->setPosition(width - 80, 40);
		scoreText->setCharacterSize(30);
		fuelNum->setPosition(width - 30, 20);
		fuelNum->setCharacterSize(30);
		scoreNum->setPosition(width - 30, 40);
		scoreNum->setCharacterSize(30);
	}
	void updateStats(Player *p) {
		fuel = p->getFuel();
		score = p->getScore();
		if (fuel >= 0) {
			fuelNum->setString(to_string(fuel));
		}
		scoreNum->setString(to_string(score));
	}
	void drawStats(sf::RenderWindow* win) {
		win->draw(*fuelText);
		win->draw(*scoreText);
		win->draw(*fuelNum);
		win->draw(*scoreNum);
	}

};



#endif
