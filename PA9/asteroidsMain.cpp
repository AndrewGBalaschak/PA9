#include "AsteroidsArray.h"

int test(void)
{
	srand(time(NULL));
	RenderWindow window(VideoMode(2000, 2000), "SFML");
	window.setFramerateLimit(60);
	Texture texture;

	texture.setSmooth(true);
	texture.loadFromFile("asteroidTexture.jpg");
	
	Asteroid::texture = &texture;
	Asteroid::window = &window;

	AsteroidsArray asteroidsArray; 
	asteroidsArray.spawnAsteroid();

	int i = 0;

	while (window.isOpen())
	{
		Event event; 
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		i++;
		window.clear();
		if (i % 60 == 0)
		{
			asteroidsArray.spawnAsteroid();
		}
		asteroidsArray.drawAsteroids();
		window.display();
	}
	return 0;
}
