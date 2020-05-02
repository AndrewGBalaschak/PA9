#include "Asteroid.h"

class AsteroidsArray
{
	private:
		Asteroid** asteroidsArray;
		int numAsteroids;
		bool* destroyedAsteroids;

	public:
		AsteroidsArray();
		void drawAsteroids(void);
		void spawnAsteroid(void);
};
