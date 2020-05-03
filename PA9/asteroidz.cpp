#include "MovingObject.h"

void checkForCollisions(std::vector<MovingObject*> objs) {
	for (int i = 0; i < objs.size() - 1; i++) {
		for (int j = i + 1; j < objs.size(); j++) {
			if (objs[i]->collides(objs[j])) {
				objs[i]->collideResults();
				objs[j]->collideResults();
			}
		}
	}
}
