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

public:
	Timer() { //default 3 minutes for multi player
		minutes = 3;
		seconds = 0;
		count = 0;
		setTimerNum(3, 0);
	}
	Timer(int m, int s) {
		minutes = m;
		seconds = s;
		setTimerNum(m, s);
	}
	void setStart(time_t s) {
		start = s;
	}
	void setTimerNum(int m, int s) {
		timerNum = (m * 60) + s;
	}

	bool Timer::countdown() {
		time_t current;
		time(&current);
		if (count == timerNum) {
			cout << "TIME IS UP!";
			return false;
		}
		else if (current == start + count + 1) {
			if (seconds == 0) {
				seconds = 60;
				minutes--;
			}
			seconds--;
			count++;
			return true;
		}
		int getMin() {
			return minutes;
		}
		int getSec() {
			return seconds;
		}
	}
};
