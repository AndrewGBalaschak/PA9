#ifndef ASTEROID_H
#define ASTEROID_H

#include "Player.h"
#include "Projectile.h"
#include "MovingObject.h"


class Asteroid : public MovingObject
{
private:
	Vector2f position; //x, y position of the center of the asteroids
	Vector2f velocity; //x and y components of asteroid velocity
	ConvexShape asteroidShape; //ConvexShape object used to draw the asteroid
	float angularFrequency; //number of degrees rotated every frame
	int size[4]; //length of each of the four arms of the rectangle
	int centerOfMassX; //x position of center of mass relative to the center of the asteroid
	int centerOfMassY; //y position of center of mass relative to the center of the asteroid
	int* xOffsets; //x position of all points of ConvexShape (i.e., the asteroid shape) relative to the asteroid's center
	int* yOffsets; //y position of all points of ConvexShape (i.e., the asteroid shape) relative to the asteroid's center 
	int extremes[4]; //x and y position of the four arms of the asteroid rectangle relative to the origin of the screen (top-left corner)
	bool collidesPlayer; //true if asteroid has collided with the player; false otherwise
	bool collidesBullet;  //true if asteroid has collided with a player's bullet; false otherwise

public:
	static int pointsPerSide; //points drawn for each of the four sides of the asteroid - this is common to all asteroids (hence static)
	static RenderWindow* window; //window to which asteroid is drawn (again common to all asteroids)
	static Texture* texture; //asteroid texture (an image file)
	static float angularFrequencyLimit; //angular frequency is randomly assigned - this gives the upper bound (loewr bound is 0)
	static int speedLimit; //velocity is randomly assigned an integer on [-speedLimit, 0) U (0, speedLimit]
	static int sizeLimit; //maximum length of the each of the four arms (again arm lengths are randomly assigned on [sizeLimit / 2, sizeLimit])
	static int screenDimensions[2]; //width (horizontal) and length (horizontal) of the drawing window 

	Asteroid(); //default constructor


	void generateShape(void); //generates the ConvexShape used to represent the asteroid
	void move(void); //moves the asteroid according to its velocity vector and angular frequency
	void drawAsteroid(void); //draws the asteroid onto the given drawing window
	void generateVelocity(void); //generates random velocity vector
	void generatePosition(void); //generates a position such that the asteroid emerges from offscreen
	void generateSize(void); //generates a random size for the asteroid (i.e., randomly generates each of its four arms)

	
	bool collides(MovingObject* movingObject) //redefined pure virtual function from MovingObject class
	{
		return false;
	}
	
	
	void collideResults(void) //redefined pure virtual function
	{
	}

	bool collides_(Projectile* bulletObj) //returns true if asteroid has collided with the given bullet object, false otherwise
	{
		
		bool hasCollided = false; //boolean to return
		int bulletX = 0; //x and y positions of the bullet
		int bulletY = 0;

		bulletX = bulletObj->getX(); //get x and y coordinates of the bullet
		bulletY = bulletObj->getY();

		hasCollided = hasCollidedWithPosition(bulletX, bulletY); //use hasCollided function, which checks to see if the given position is within the rectangle of the asteroid
		collidesBullet = hasCollided; //update the collidesBullet member boolean
		if (hasCollided) {
			bulletObj->isDead();
			isDead();
		}
		std::cout << "COLLIDES BULLET: " << hasCollided << std::endl;
		return hasCollided;
	}

	bool collides_(Player* playerObj) //returns true if the asteroid has collided with the player, false otherwise
	{
		bool hasCollided = false;
		int playerX = 0;
		int playerY = 0;

		playerX = playerObj->getX();
		playerY = playerObj->getY();

		hasCollided = hasCollidedWithPosition(playerX, playerY);
		collidesPlayer = hasCollided;
		if (hasCollided) playerObj->isDead();
		std::cout << "COLLIDES PLAYER: " << hasCollided << std::endl;
		return hasCollided;
	}

	void updateSprite(void) //redefined pure virtual function
	{

	}

	sf::FloatRect getBounds() {
		return asteroidShape.getGlobalBounds();
	}

	void draw(RenderWindow* renderWindow) //redefined pure virtual function
	{

	}

	void updateExtremes(void) //update the position of the four arms of the asteroid's rectangle
	{
		int asteroidX = 0;
		int asteroidY = 0;


		asteroidX = asteroidShape.getPosition().x;
		asteroidY = asteroidShape.getPosition().y;

		
		extremes[0] = asteroidY + centerOfMassY + size[0];
		extremes[1] = asteroidX - centerOfMassX - size[1];
		extremes[2] = asteroidY - centerOfMassY - size[2];
		extremes[3] = asteroidX + centerOfMassX + size[3];

	}

	bool hasCollidedWithPosition(int x, int y)
	{
		bool hasCollided = false;

		hasCollided = x >= extremes[1] && x <= extremes[3] && y <= extremes[0] && y >= extremes[2];

		return hasCollided;

	}

	bool isOffScreen(void);

	bool getCollidesPlayer(void) const
	{
		return collidesPlayer;
	}

	bool getCollidesBullet(void) const
	{
		return collidesBullet;
	}
	
	void updatePosition(void) {}
	void isDead() { active = false; }
};

int getRandomIntOnRange(int, int);
int* getRandomSequenceOnRange(int, int, int);
void selectionSortRecursive(int*, int, bool);
int getMinIndex(int*, int);
int getMaxIndex(int*, int);
void swap(int*, int, int);
float getRandomFloatOnRange(int, int);
float getCenter(float, float);
int leftRiemannSum(int*, int*, int);
void printArray(int*, int);

#endif
