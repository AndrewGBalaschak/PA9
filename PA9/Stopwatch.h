#include "Timer.h"

class Stopwatch : public Timer {
private:
	time_t prevRevival;

public:
	Stopwatch(int m, int s) :Timer(m, s) {
		prevRevival = start;
	}
	void aliveTime() {
		time_t current;
		time(&current);
		int totSec = 0;
		totSec = current - prevRevival;

		minutes = totSec / 60;
		seconds = totSec % 60;
	}
};
