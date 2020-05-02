#ifndef PLAYER_H
#define PLAYER_H

#define PI 3.14159265358979323846

#include "MovingObject.h"
#include <iostream>
#include <math.h>
using namespace std;

class Player : public MovingObject {
protected:
	int score;
	int fuel;
	int fuelConsumptionRate; //debug
	double moveSpeed; //debug
	double rotateSpeed; //debug
	double maxVelocity; //debug
	struct Scalar { //dictates what proportion of the player's acceleration goes into x and y components of velocity
		double x; //proportion of acceleration in x direction (-1 to 1)
		double y; //proportion of acceleration in y direaction (-1 to 1)
	};
	Scalar s;
	sf::Sprite* playerSprite;
	sf::Texture* playerTexture;
	sf::RectangleShape *r1, *r2, *r3;
public:
	Player(int x, int y) {
		score = 0;
		fuel = 500;
		fuelConsumptionRate = 1;
		moveSpeed = .1;
		rotateSpeed = .05;
		maxVelocity = 5;
		rotation = PI / 2;//player is facing straight
		p.x = x;
		p.y = y;
		v.x = 0;
		v.y = 0;
		s.x = 0;
		s.y = 1;
		radius = 20;
		active = true;
		//loading image
		playerTexture = new sf::Texture();
		playerTexture->loadFromFile("Player.png");
		playerSprite = new sf::Sprite;
		playerSprite->setTexture(*playerTexture);
		playerSprite->setPosition(p.x, p.y);
		playerSprite->setOrigin(16, 16);
		
		//loading collision boxes
		r1 = new sf::RectangleShape(sf::Vector2f(32, 2));
		r1->setFillColor(sf::Color::Red);
		r1->setOrigin(sf::Vector2f(18, 5));
		r2 = new sf::RectangleShape(sf::Vector2f(32, 2));
		r2->setFillColor(sf::Color::Red);
		r2->setOrigin(sf::Vector2f(18, -3));
		r3 = new sf::RectangleShape(sf::Vector2f(15, 2));
		r3->setFillColor(sf::Color::Red);
		r3->setOrigin(sf::Vector2f(7, -13));
		
	}

	//return fuel for stats
	int getFuel() {
		return fuel;
	}
	//return score for stats
	int getScore() {
		return score;
	}
	int getVelX() {
		return v.x;
	}
	int getVelY() {
		return v.y;
	}
	
	//calculates what proportion of thrust should go into x and y components
	void calculateScalar() {
		s.x = cos(rotation);
		s.y = sin(rotation);
	}

	//rotates object left, affected by rotateSpeed
	void rotateLeft() {
		rotation += rotateSpeed;
		if (rotation > (2 * PI)) rotation -= (2 * PI);
		calculateScalar();
	}

	//rotates object right, affected by rotateSpeed
	void rotateRight() {
		rotation -= rotateSpeed;
		if (rotation < 0) rotation = 2 * PI + rotation;
		calculateScalar();
	}

	//accelerates forward by moveSpeed, limit is maxVelocity
	void accelerateForward() {
		if (fuel > 0) {
			//FOR X
			//velocity adjustment will not be applied if velocity is over max
			if (abs(v.x) < maxVelocity) {
				v.x += moveSpeed * s.x;
			}
			//unless the adjustment decreases the velocity
			else if (abs(v.x + (moveSpeed * s.x)) < maxVelocity) {
				v.x += moveSpeed * s.x;
			}
			//FOR Y
			//velocity adjustment will not be applied if velocity is over max
			if (abs(v.y) < maxVelocity) {
				v.y += moveSpeed * s.y;
			}
			//unless the adjustment decreases the velocity
			else if (abs(v.y + (moveSpeed * s.y)) < maxVelocity) {
				v.y += moveSpeed * s.y;
			}
			fuel -= fuelConsumptionRate;
		}
	}

	//accelerates reverse by moveSpeed, limit is maxVelocity
	void accelerateReverse() {
		if (fuel > 0) {
			//FOR X
		//velocity adjustment will not be applied if velocity is over max
			if (abs(v.x) < maxVelocity) {
				v.x -= moveSpeed * s.x;
			}
			//unless the adjustment decreases the velocity
			else if (abs(v.x - (moveSpeed * s.x)) < maxVelocity) {
				v.x -= moveSpeed * s.x;
			}

			//FOR Y
			//velocity adjustment will not be applied if velocity is over max
			if (abs(v.y) < maxVelocity) {
				v.y -= moveSpeed * s.y;
			}
			//unless the adjustment decreases the velocity
			else if (abs(v.y - (moveSpeed * s.y)) < maxVelocity) {
				v.y -= moveSpeed * s.y;
			}
			fuel -= fuelConsumptionRate;
		}
	}
	void updateSprite() {
		playerSprite->setPosition(p.x, p.y);
		playerSprite->setRotation(90 - getRotationDegrees());
		r1->setPosition(p.x, p.y);
		r1->setRotation(15 - getRotationDegrees());
		r2->setPosition(p.x, p.y);
		r2->setRotation(342 - getRotationDegrees());
		r3->setPosition(p.x, p.y);
		r3->setRotation(90 - getRotationDegrees());
		cout << getRotationDegrees() << endl;
	}
	void draw(sf::RenderWindow *win) {
		win->draw(*r1);
		win->draw(*r2);
		win->draw(*r3);
		win->draw(*playerSprite);
	}

	bool collides(MovingObject *obj) {
		//Collision::PixelPerfectTest(*playerSprite, obj->)
		return false;
	}

	void collideResults() {
		// do something
	}
};
#endif;