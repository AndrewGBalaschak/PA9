#include "Stopwatch.h"

void Stopwatch::aliveTime() {
	time_t current;
	time(&current);
	int totSec = 0;
	totSec = current - prevRevival;

	minutes = totSec / 60;
	seconds = totSec % 60;
}