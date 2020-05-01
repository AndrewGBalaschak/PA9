#ifndef STATS_H
#define STATS_H

class Stats {
private:
	sf::Text* fuel, * score, *fuelText, *scoreText;
	sf::Font font;
public:
	Stats() {
		if (!font.loadFromFile("Tuffy.otf")) cout << "ERROR";

		fuel = new sf::Text(to_string(0), font);
		score = new sf::Text(to_string(0), font);
		fuelText = new sf::Text("Fuel: ", font);
		scoreText = new sf::Text("Score: ", font);

		fuelText->setPosition(width - 80, 50);
		fuelText->setCharacterSize(15);
		scoreText->setPosition(width - 80, 70);
		scoreText->setCharacterSize(15);
		fuel->setPosition(width - 30, 50);
		fuel->setCharacterSize(15);
		score->setPosition(width - 30, 70);
		score->setCharacterSize(15);
	}
	void updateStats(int f, int s) {
		if (f >= 0) {
			fuel->setString(to_string(f));
		}
		score->setString(to_string(s));
	}
	void drawStats(sf::RenderWindow* win) {
		win->draw(*fuelText);
		win->draw(*scoreText);
		win->draw(*fuel);
		win->draw(*score);
	}

};



#endif