#ifndef ASTEROID_H
#define ASTEROID_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
using namespace sf;


class Asteroid : public MovingObject
{
	private:
		//Vector2f size;
		Vector2f position;
		Vector2f velocity;
		ConvexShape asteroidShape;
		float angularFrequency; 
		int size[4];
		int centerOfMassX;
		int centerOfMassY;
		int* xOffsets;
		int* yOffsets;
		int extremes[4];
	
	public:
		static int pointsPerSide;
		static RenderWindow* window;
		static Texture* texture;
		static float angularFrequencyLimit;
		static int speedLimit;
		static int sizeLimit; 
		static int screenDimensions[2];

		Asteroid();


		void generateShape(void);
		void setXPosition(float);
		void setYPosition(float);
		void setXVelocity(float);
		void setYVelocity(float);
		void setVelocity(Vector2f);
		void setPosition(Vector2f);
		void move(void);
		void updatePosition(void);
		void drawAsteroid(void);
		void generateVelocity(void);
		void generatePosition(void);
		void generateSize(void);
		bool collides(MovingObject *)
		{
			
		}
		
		bool collides(RectangleShape *bulletObj)
		{
			bool hasCollided = false;
			int bulletX = 0;
			int bulletY = 0;
		
			bulletX = bulletObj->getPosition().x;
			bulletY = bulletObj->getPosition().y;
			
			hasCollided = hasCollidedWithPosition(bulletX, bulletY);

			return hasCollided;
		}
		
		bool collides(Player *playerObj)
		{
			bool hasCollided = false;
			int playerX = 0;
			int playerY = 0;
		
			playerX = playerObj->getX();
			playerY = playerObj->getY();
			
			hasCollided = hasCollidedWithPosition(playerX, playerY);

			return hasCollided;
			
		}
		
		void updateExtremes(void)
		{
			int asteroidX = 0;
			int asteroidY = 0;
			
			
			asteroidX = asteroidShape.getPosition().x;
			asteroidY = asteroidShape.getPosition().y;
			
			for(int i = 0; i < 2; i++)
			{
				extremes[2*i] = size[2*i] + asteroidY - centerOfMassY;
				extremes[2*i + 1] = size[2*i + 1] + asteroidX - centerOfMassX;
			}
		
			
		}
		
		bool hasCollidedWithPosition(int x, int y)
		{
			bool hasCollided = false;
			
			hasCollided = x >= extremes[1] && x <= extremes[3] && y >= extremes[0] && y <= extremes[2];
			
			return hasCollided;
		
		}
		
		bool isOffScreen(void);

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
