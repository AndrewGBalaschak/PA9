#include "AsteroidsArray.h"

void AsteroidsArray::drawAsteroids(void)
{
	Asteroid* currentAsteroid = nullptr;
	bool currentDestroyed = 0;
	

	for (int i = 0; i < numAsteroids; i++)
	{
		currentAsteroid = asteroidsArray[i];
		currentDestroyed = destroyedAsteroids[i];
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
	Asteroid* newAsteroid = new Asteroid;
	asteroidsArray = (Asteroid **) realloc(asteroidsArray, ++numAsteroids * sizeof(Asteroid*));
	destroyedAsteroids = (bool*) realloc(destroyedAsteroids, numAsteroids * sizeof(bool));

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
