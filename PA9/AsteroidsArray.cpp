#include "AsteroidsArray.h"

void AsteroidsArray::drawAsteroids(void)
{
	Asteroid* currentAsteroid = nullptr;
	bool currentDestroyed = 0;

	asteroidsDestroyed = 0;

	for (int i = 0; i < numAsteroids; i++)
	{
		currentAsteroid = asteroidsArray[i];
		currentDestroyed = destroyedAsteroids[i];
		std::cout << "DESTROYED: " << currentAsteroid << ", " << i << ", " << currentDestroyed << std::endl;
		if (currentDestroyed == false)
		{
			if (currentAsteroid->isOffScreen() == true)
			{
				currentAsteroid->isDead();
				destroyedAsteroids[i] = true;
			}
			else if (currentAsteroid->getCollidesPlayer() == true)
			{
				gameOver = true;
				asteroidsDestroyed++;
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
				std::cout << "CURRENT_ASTEROID" << currentAsteroid;

				currentAsteroid->move();
				if (currentAsteroid->getActive())
					currentAsteroid->drawAsteroid();
				else {
					destroyedAsteroids[i] = true;
					delete currentAsteroid;
				}
			}

		}

	}

}

Asteroid* AsteroidsArray::spawnAsteroid(void)
{
	Asteroid* newAsteroid = new Asteroid;
	asteroidsArray = (Asteroid **) realloc(asteroidsArray, ++numAsteroids * sizeof(Asteroid*));
	destroyedAsteroids = (bool*) realloc(destroyedAsteroids, numAsteroids * sizeof(bool));

	destroyedAsteroids[numAsteroids - 1] = false;
	asteroidsArray[numAsteroids - 1] = newAsteroid;
	return newAsteroid;
}

AsteroidsArray::AsteroidsArray()
{
	numAsteroids = 0;
	asteroidsArray = nullptr;
	destroyedAsteroids = nullptr;
	gameOver = false;
}

void AsteroidsArray::checkForCollisions(std::vector<Projectile *> &objs, Player &p) {
	Asteroid *currentAsteroid = nullptr;
	bool currentDestroyed = 0;

	asteroidsDestroyed = 0;

	for (int i = 0; i < numAsteroids; i++) {
		currentAsteroid = asteroidsArray[i];
		currentDestroyed = destroyedAsteroids[i];
		std::cout << "DESTROYED: " << currentAsteroid << ", " << i << ", " << currentDestroyed << std::endl;
		if (currentDestroyed == false) {
			currentAsteroid->collides_(&p);
			for (int i = 0; i < objs.size(); i++)
				currentAsteroid->collides_(objs[i]);
		}
	}
}