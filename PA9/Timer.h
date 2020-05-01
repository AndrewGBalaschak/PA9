#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <ctime>

using namespace std;

class Timer { //timer must be called at beginning of game start
protected:
	int minutes;
	int seconds;
	int timerNum;
	int count;
	time_t start;

	bool timerStart;
	sf::Text* min, * colon, * sec, * zero;
	sf::Font font;

public:
	Timer() { //default 3 minutes for multi player
		minutes = 3;
		seconds = 0;
		count = 0;
		timerStart = true;
		time(&start);

		if (!font.loadFromFile("Tuffy.otf")) cout << "ERROR";

		min = new sf::Text("3", font);
		colon = new sf::Text(":", font);
		sec = new sf::Text("0", font);
		zero = new sf::Text("0", font);

		min->setPosition(width - 80, 7);
		min->setCharacterSize(30);
		colon->setPosition(width - 60, 5);
		colon->setCharacterSize(30);
		sec->setPosition(width - 45, 7);
		sec->setCharacterSize(30);
		zero->setPosition(width - 45, 7);
		zero->setCharacterSize(30);
		setTimerNum(3, 0);
	}
	Timer(int m, int s) {
		minutes = m;
		seconds = s;
		setTimerNum(m, s);
	}
	void setStart() {
		time(&start);
		timerStart = true;
	}
	void setTimerNum(int m, int s) {
		timerNum = (m * 60) + s;
	}

	void countdown() {
		time_t current;
		time(&current);
		if (count == timerNum) {
			cout << "TIME IS UP!";
			timerStart = false;
		}
		else if (current == start + count + 1) {
			if (seconds == 0) {
				seconds = 60;
				minutes--;
			}
			seconds--;
			count++;
			timerStart = true;
		}
		update();
	}
	int getMin() {
		return minutes;
	}
	int getSec() {
		return seconds;
	}
	bool getStart() {
		return timerStart;
	}
	void update() {
		min->setString(to_string(minutes));
		sec->setString(to_string(seconds));
	}
	void drawTimer(sf::RenderWindow* win) {
		if (seconds < 10) {
			win->draw(*zero);
			sec->setPosition(width - 28, 7);
		}
		else {
			sec->setPosition(width - 45, 7);
		}
		win->draw(*min);
		win->draw(*colon);
		win->draw(*sec);
	}
};


#endif // !TIMER_H
