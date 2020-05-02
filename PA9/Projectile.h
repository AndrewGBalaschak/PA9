#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Player.h"

class Projectile : public MovingObject {
private:
	//start at player location and 
	//go in straight line with increased constant velocity
	sf::CircleShape* bullet;

public:
	Projectile(int playerX, int playerY, double deg) {
		bullet = new sf::CircleShape(2.f, 4);
		bullet->setFillColor(sf::Color());
		active = true;
		setLocation(playerX, playerY, deg);
	}
	~Projectile() {
		delete bullet;
	}

	void setLocation(int playerX, int playerY, double deg) {
		p.x = playerX;
		p.y = playerY;
		rotation = deg;
		v.x = 8 * cos(deg);
		v.y = 8 * sin(deg);
	}
	void updatePosition() {
		if (active) {
			p.x += v.x;
			p.y -= v.y;
		}
		if (p.x <= 0 || p.x >= width || p.y <= 0 || p.y >= height) {
			active = false;
		} else {
			active = true;
		}
		updateSprite();
	}
	void updateSprite() {
		bullet->setPosition(p.x, p.y);
		bullet->setRotation(rotation);

	}
	int getX() {
		return p.x;
	}
	int getY() {
		return p.y;
	}
	void draw(sf::RenderWindow* win) {
		if (active) {
			bullet->setFillColor(sf::Color(255, 255, 255));
			win->draw(*bullet);
		}
	}

	bool collides(MovingObject *obj) {
		return false;
	}

	sf::FloatRect getBounds() {
		return bullet->getGlobalBounds();
	}

	void collideResults() {
		active = false;
	}
};

#endif // !PROJECTILE_H