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

	sf::Text* min, * colon, * sec, * zero;
	sf::Font font;

	bool timerStart;

public:
	Timer() { //default 3 minutes
		minutes = 0;
		seconds = 10;
		count = 0;
		time(&start);
		timerStart = true;

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

	void setStart() {
		time(&start);
		timerStart = true;
	}

	bool getStart() {
		return timerStart;
	}
	
	void setTimerNum(int m, int s) {
		timerNum = (m * 60) + s;
	}

	bool countdown() {
		time_t current;
		time(&current);
		if (minutes == 0 && seconds == 0) {
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
		return timerStart;
	}
	
	int getMin() {
		return minutes;
	}
	int getSec() {
		return seconds;
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
