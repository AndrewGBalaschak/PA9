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
				delete currentAsteroid;
				destroyedAsteroids[i] = true;
			}
			else if (currentAsteroid->getCollidesPlayer() == true)
			{
				gameOver = true;
			}
			else if (currentAsteroid->getCollidesBullet() == true)
			{
				asteroidsDestroyed++;
				delete currentAsteroid;
				destroyedAsteroids[i] = true;
			}
			else
			{
				std::cout << "CURRENT_ASTEROID" << currentAsteroid;

				currentAsteroid->move();
				currentAsteroid->drawAsteroid();
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
