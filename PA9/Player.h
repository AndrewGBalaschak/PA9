#ifndef PLAYER_H
#define PLAYER_H

#define PI 3.14159265358979323846

#include "MovingObject.h"
#include <iostream>
#include <math.h>
using namespace std;

class Player : public MovingObject {
private:
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

public:

	Player(int x, int y) {
		score = 0;
		fuel = 500;
		fuelConsumptionRate = 5;
		moveSpeed = .1;
		rotateSpeed = .05;
		maxVelocity = 5;
		rotation = PI / 2; //player is facing straight up
		p.x = x;
		p.y = y;
		v.x = 0;
		v.y = 0;
		s.x = 0;
		s.y = 1;
		radius = 16;
		//loading the image
		playerTexture = new sf::Texture();
		playerTexture->loadFromFile("Player.png");
		playerSprite = new sf::Sprite;
		playerSprite->setTexture(*playerTexture);
		playerSprite->setPosition(p.x, p.y);
		playerSprite->setOrigin(16, 16);

		/*playerSprite = new sf::CircleShape(radius, 3);
		playerSprite->setFillColor(sf::Color(255, 255, 255));
		playerSprite->setPosition(p.x, p.y);
		playerSprite->setOrigin(radius, radius);
		*/
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

	//accelerates reverse by moveSpeed, limit is maxVelocity
	void accelerateReverse() {
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

	void updateSprite() {
		updatePosition();
		playerSprite->setPosition(p.x, p.y);
		playerSprite->setRotation(90 - getRotationDegrees());
	}

	sf::Sprite getSprite() {
		return *playerSprite;
	}

	void collideResults() {
		// finish after
	}
};
#endif;