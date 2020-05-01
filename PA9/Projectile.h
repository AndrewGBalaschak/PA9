#ifndef PROJECTILE_H
#define PROJECTILE_H

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
	double angle;
	bool activate = false;
	sf::CircleShape* bullet;

public:
	Projectile() {
		r.x = 0;
		r.y = 0;
		v.x = 0;
		v.y = 0;
		angle = PI / 2;
		bullet = new sf::CircleShape(2.f, 4);
		bullet->setFillColor(sf::Color(255, 255, 255));
	}
	Projectile(int playerX, int playerY) {
		r.x = playerX;
		r.y = playerY;
		v.x = 0;
		v.y = 0;
		angle = PI / 2;
	}
	void setLocation(int playerX, int playerY, double deg) {
		r.x = playerX;
		r.y = playerY;
		angle = deg;
		v.x = 8 * cos(deg);
		v.y = 8 * sin(deg);
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
	void updateSprite() {
		bullet->setPosition(r.x, r.y);
		bullet->setRotation(360 - angle);
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
	void drawBullet(sf::RenderWindow* win) {
		if (isActivated())
			win->draw(*bullet);
	}
};


#endif // !PROJECTILE_H
