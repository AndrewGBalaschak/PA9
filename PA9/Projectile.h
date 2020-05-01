#include "Player.h"

class Projectile {
private:
	//start at player location and 
	//go in straight line with increased constant velocity
	struct projPos {
		int x;
		int y;
	};
	struct projVel {
		int x;
		int y;
	};
	projPos r;
	projVel v;
	bool activate = false;

public:
	Projectile() {
		r.x = 0;
		r.y = 0;
		v.x = 0;
		v.y = 0;
	}
	Projectile(int playerX, int playerY) {
		r.x = playerX;
		r.y = playerY;
		v.x = 0;
		v.y = 0;
	}
	void setLocation(int playerX, int playerY, double angle) {
		r.x = playerX;
		r.y = playerY;
		v.x = 8 * cos(angle);
		v.y = 8 * sin(angle);
	}
	void updateLocation() {
		if (activate) {
			r.x += v.x;
			r.y -= v.y;
		}
		if (r.x < 0 || r.x > 800 || r.y < 0 || r.y>600)
			activate = false;
		shoot();
	}
	void shoot() {
		activate = true;
	}
	int getX() {
		return r.x;
	}
	int getY() {
		return r.y;
	}
	bool isActivated() {
		return activate;
	}
};
