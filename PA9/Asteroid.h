#ifndef ASTEROID_H
#define ASTEROID_H

#include "MovingObject.h"
#include <iostream>
using namespace std;

class Asteroid : MovingObject {
private:
	struct Position {
		int x;
		int y;
	};
	struct Velocity {
		int x;
		int y;
	};

public:

};
#endif;