#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#define PI 3.14159265358979323846

#include <iostream>
using namespace std;

class MovingObject {
protected:
	struct Position {
		double x; //x coordinate
		double y; //y coordinate
	};

	struct Velocity {
		double x; //x component of velocity
		double y; //y component of velocity
	};

	Position p;
	Velocity v;
	double rotation; //angle the object is facing in radians
	double radius;
	bool active;

public:
	virtual ~MovingObject() {};

	//returns object X coordinate
	int getX() {
		return p.x;
	}

	//returns object Y coordinate
	int getY() {
		return p.y;
	}

	//returns object rotation in radians
	double getRotation() {
		return rotation;
	}

	//returns if object is active
	bool getActive() {
		return active;
	}

	//returns object rotation in degrees, converted from radians
	double getRotationDegrees() {
		return rotation * 180 / PI;
	}

	//updates the coordinates of the object
	virtual void updatePosition() {
		p.x += v.x;
		p.y -= v.y;

		if (v.x == 0) {
			if (p.y < 0) {
				p.y = 600;
			}
			else if (p.y > 600) {
				p.y = 0;
			}
		}
		else if (v.y == 0) {
			if (p.x < 0) {
				p.x = 800;
			}
			else if (p.x > 800) {
				p.x = 0;
			}
		}
		else if (p.x < 0 || p.x > 800) {
			p.y = 600 - p.y;
			if (p.x < 0) {
				p.x = 800;
			}
			else {
				p.x = 0;
			}
		}

		else if (p.y < 0 || p.y > 600) {
			p.x = 800 - p.x;
			if (p.y < 0) {
				p.y = 600;
			}
			else {
				p.y = 0;
			}
		}

		updateSprite();
	}

	virtual void updateSprite() = 0;
	virtual void draw(sf::RenderWindow *) = 0;
	virtual bool collides(MovingObject *) = 0;
	virtual void collideResults() = 0;

};

void checkForCollisions(vector<MovingObject *> objs) {
	for (int i = 0; i < objs.size()-1; i++) {
		for (int j = i+1; j < objs.size(); j++) {
			if (objs[i]->collides(objs[j])) {
				objs[i]->collideResults();
				objs[j]->collideResults();
			}
		}
	}
}

#endif;