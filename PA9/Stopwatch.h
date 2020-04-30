#include "Timer.h"

class Stopwatch :public Timer {
private:
	time_t prevRevival;

public:
	Stopwatch(int m, int s) :Timer(m, s) {
		prevRevival = start;
	}
	void aliveTime();
};