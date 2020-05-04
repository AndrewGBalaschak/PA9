#include "AsteroidsArray.h"

void AsteroidsArray::drawAsteroids(void)
{
	Asteroid* currentAsteroid = nullptr;
	bool currentDestroyed = 0;
	
	//iterate through all asteroids that have been spawned
	for (int i = 0; i < numAsteroids; i++)
	{
		currentAsteroid = asteroidsArray[i]; //get the current asteroid
		currentDestroyed = destroyedAsteroids[i]; 
		if (currentDestroyed == false) //if the current asteroid has already been destroyed, then don't do anything
		{
			if (currentAsteroid->isOffScreen() == true) //if asteroid is offscreen or has collided with a bullet or player, destroy the asteroid and make the appropriate changes
			{
				currentAsteroid->isDead();
				destroyedAsteroids[i] = true;
			}
			else if (currentAsteroid->getCollidesPlayer() == true)
			{
				gameOver = true;
				currentAsteroid->isDead();
				destroyedAsteroids[i] = true;
			}
			else if (currentAsteroid->getCollidesBullet() == true)
			{
 				asteroidsDestroyed++;
				currentAsteroid->isDead();
				destroyedAsteroids[i] = true;
			}
			else
			{
				currentAsteroid->move();
				if (currentAsteroid->getActive())
					currentAsteroid->drawAsteroid();
				else {
					asteroidsDestroyed++;
					destroyedAsteroids[i] = true;
					delete currentAsteroid;
				}
			}

		}

	}

}

Asteroid* AsteroidsArray::spawnAsteroid(void) 
{
	Asteroid* newAsteroid = new Asteroid; //dynamically allocate a new asteroid
	asteroidsArray = (Asteroid **) realloc(asteroidsArray, ++numAsteroids * sizeof(Asteroid*)); //increase the size of the asteroids array by one to make room for the new asteroid
	destroyedAsteroids = (bool*) realloc(destroyedAsteroids, numAsteroids * sizeof(bool)); //same for destroyed asteroids array

	destroyedAsteroids[numAsteroids - 1] = false;
	asteroidsArray[numAsteroids - 1] = newAsteroid;
	return newAsteroid;
}

AsteroidsArray::AsteroidsArray()
{
	asteroidsDestroyed = 0;
	numAsteroids = 0;
	asteroidsArray = nullptr;
	destroyedAsteroids = nullptr;
	gameOver = false;
}

void AsteroidsArray::checkForCollisions(std::vector<Projectile *> &objs, Player &p) {
	Asteroid *currentAsteroid = nullptr;
	bool currentDestroyed = 0;

	for (int i = 0; i < numAsteroids; i++) {
		currentAsteroid = asteroidsArray[i];
		currentDestroyed = destroyedAsteroids[i];
		if (currentDestroyed == false) {
			currentAsteroid->collides_(&p);
			for (int i = 0; i < objs.size(); i++) {
				if (objs[i]->getActive() == true)
					currentAsteroid->collides_(objs[i]);
			}
		}
	}
}
