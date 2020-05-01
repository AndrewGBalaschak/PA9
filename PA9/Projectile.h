#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Player.h"

class Projectile : public MovingObject {
private:
	bool activate = false;
	sf::CircleShape* bullet;

public:
	Projectile(int playerX, int playerY) {
		p.x = playerX;
		p.y = playerY;
		v.x = 0;
		v.y = 0;
		rotation = PI / 2;
		bullet = new sf::CircleShape(2.f, 4);
		bullet->setFillColor(sf::Color());
	}
	void setLocation(int playerX, int playerY, int playerVx, int playerVy, double deg) {
		p.x = playerX;
		p.y = playerY;
		rotation = deg;
		v.x = (abs(playerVx)+8) * cos(deg);
		v.y = (abs(playerVy)+8) * sin(deg);
	}
	void updateLocation() {
		if (activate) {
			p.x += v.x;
			p.y -= v.y;
		}
		if (p.x < 0 || p.x > 800 || p.y < 0 || p.y>600)
			activate = false;
		shoot();
	}
	void updateSprite() {
		bullet->setPosition(p.x, p.y);
		bullet->setRotation(360 - rotation);

	}
	void shoot() {
		activate = true;
	}
	int getX() {
		return p.x;
	}
	int getY() {
		return p.y;
	}
	void drawBullet(sf::RenderWindow* win) {
		if (activate) {
			bullet->setFillColor(sf::Color(255, 255, 255));
			win->draw(*bullet);
		}
	}

	void collideResults(MovingObject &collided) {
		// do something
	}
};


#endif // !PROJECTILE_H
