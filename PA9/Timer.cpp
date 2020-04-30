#include "Timer.h"

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
}
