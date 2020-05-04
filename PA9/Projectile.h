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

	//has the initial location and angle as the player, but increased velocity
	void setLocation(int playerX, int playerY, double deg) {
		p.x = playerX;
		p.y = playerY;
		rotation = deg;
		v.x = 15 * cos(deg);
		v.y = 15 * sin(deg);
	}

	//basically move the projectile object in a straight line and then stop when its off window
	void updatePosition() {
		if (active) {
			p.x += v.x;
			p.y -= v.y;
		}
		if (p.x <= 0 || p.x >= WIDTH || p.y <= 0 || p.y >= HEIGHT) {
			active = false;
		}
		else {
			active = true;
		}
		updateSprite();
	}

	//according to the position of the object, the sprite on screen will be updated
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

	//draw bullet on screen
	void draw(sf::RenderWindow* win) {
		if (active) {
			bullet->setFillColor(sf::Color(255, 255, 255));
			win->draw(*bullet);
		}
	}

	//check if collides with object
	bool collides(MovingObject* obj) {// should this be changed??
		return false;
	}

	//return the area around the bullet?
	sf::FloatRect getBounds() {
		return bullet->getGlobalBounds();
	}


	void collideResults() {
		active = false;
	}
	void isDead() { active = false; }
};

#endif // !PROJECTILE_H
