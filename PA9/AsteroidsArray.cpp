#include "AsteroidsArray.h"

void AsteroidsArray::drawAsteroids(void)
{
	Asteroid* currentAsteroid = nullptr;
	bool currentDestroyed = 0;
	
	for (int i = 0; i < numAsteroids; i++)
	{
		currentAsteroid = asteroidsArray[i];
		currentDestroyed = destroyedAsteroids[i];
		std::cout << i << ", " << currentDestroyed << std::endl;
		if (currentDestroyed == false)
		{
			if (currentAsteroid->isOffScreen() == true)
			{
				delete currentAsteroid; 
				destroyedAsteroids[i] = true;
			}
			else
			{
				currentAsteroid->move();
				currentAsteroid->drawAsteroid();
			}
		}

	}

}

void AsteroidsArray::spawnAsteroid(void)
{
	Asteroid* newAsteroid = new Asteroid;
	asteroidsArray = (Asteroid**) realloc(asteroidsArray, ++numAsteroids * sizeof(Asteroid *));
	destroyedAsteroids = (bool*)realloc(destroyedAsteroids, numAsteroids * sizeof(bool));

	destroyedAsteroids[numAsteroids - 1] = false;
	asteroidsArray[numAsteroids - 1] = newAsteroid;
}

AsteroidsArray::AsteroidsArray()
{
	numAsteroids = 0;
	asteroidsArray = nullptr;
	destroyedAsteroids = nullptr;
}
