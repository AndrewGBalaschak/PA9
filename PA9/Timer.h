#ifndef TIMER_H
#define TIMER_H

#include "libraries.h"

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
		seconds = 100;
		count = 0;
		time(&start);
		timerStart = true;


		if (!font.loadFromFile("Tuffy.otf")) std::cout << "ERROR";
		
		//the objects for time display
		min = new sf::Text("3", font);
		colon = new sf::Text(":", font);
		sec = new sf::Text("0", font);
		zero = new sf::Text("0", font);

		min->setPosition(WIDTH - 80, 7);
		min->setCharacterSize(30);
		colon->setPosition(WIDTH - 60, 5);
		colon->setCharacterSize(30);
		sec->setPosition(WIDTH - 45, 7);
		sec->setCharacterSize(30);
		zero->setPosition(WIDTH - 45, 7);
		zero->setCharacterSize(30);
		setTimerNum(3, 0);
	}

	//start is set after name is entered
	void setStart() {
		time(&start);
		timerStart = true;
	}

	//get the time that the class set as start
	bool getStart() {
		return timerStart;
	}

	//total number of seconds
	void setTimerNum(int m, int s) {
		timerNum = (m * 60) + s;
	}

	//countdown loop checks until one second has passed
	bool countdown() {
		time_t current;
		time(&current);
		if (minutes == 0 && seconds == 0) {
			std::cout << "TIME IS UP!";
			timerStart = false;
		}
		//if one second has passed, then one second decrement from the seconds and minutes variables
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

	//return the minutes and seconds
	int getMin() {
		return minutes;
	}
	int getSec() {
		return seconds;
	}

	//change the minute and second displayed when a second passes
	void update() {
		min->setString(std::to_string(minutes));
		sec->setString(std::to_string(seconds));
	}

	//the timer is printed to the window in top right corner
	void drawTimer(sf::RenderWindow* win) {
		if (seconds < 10) {
			win->draw(*zero);
			sec->setPosition(WIDTH - 28, 7);
		}
		else {
			sec->setPosition(WIDTH - 45, 7);
		}
		win->draw(*min);
		win->draw(*colon);
		win->draw(*sec);
	}
};


#endif // !TIMER_H
