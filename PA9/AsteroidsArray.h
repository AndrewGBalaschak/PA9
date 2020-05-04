#ifndef ASTEROIDSARRAY_H
#define ASTEROIDSARRAY_H
#include "Asteroid.h"

class AsteroidsArray
{
private:
	Asteroid** asteroidsArray;
	int numAsteroids;
	bool* destroyedAsteroids;
	bool gameOver;
	int asteroidsDestroyed;

public:
	AsteroidsArray();
	void drawAsteroids(void);
	Asteroid* spawnAsteroid(void);
	bool getGameOver(void) const
	{
		return gameOver;
	}

	int getAsteroidsDestroyed(void) const
	{
		return asteroidsDestroyed;
	}
	void checkForCollisions(std::vector<Projectile *> &objs, Player &p);
};
#endif
