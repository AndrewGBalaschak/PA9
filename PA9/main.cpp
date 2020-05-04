/*
Programmer: Andrew Balaschak, Svetoslav Dimitrov, Seri Nakamura, Garett Pascual-Folster
Class: CPTS 122, Spring 2020; Lab Section 14
Programming Assignment:
Date:
Description:
*/

#include "Stats.h"
#include "Score.h"
#include "AsteroidsArray.h"
#include "Timer.h"

int main(void)
{
	// objects array
	std::vector<Projectile *> bullets;
	Player player(WIDTH / 2, HEIGHT / 2);
	player.setName();

	srand(time(NULL));
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "ASTEROIDZ");
	window.setFramerateLimit(50);
	Texture texture;

	texture.setSmooth(true);
	texture.loadFromFile("asteroidTexture.jpg");

	Score highscore;
	highscore.readScores();

	Stats playerStats;
	int asteroidsDestroyed = 0;

	sf::Font font;
	if (!font.loadFromFile("Tuffy.otf"))
	{
		//std::cout << "ERROR";
	}

	Asteroid::texture = &texture;
	Asteroid::window = &window;

	AsteroidsArray asteroidsArray;
	asteroidsArray.spawnAsteroid();

	//Timer class
	Timer T;

	int i = 0, j = i;
	bool contGame = true;
	//boolean to track if high score data has been written so that it is not continuously written on each loop
	bool writtenScore = false;

	T.setStart();

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

		//timer
		if (T.getStart()) {
			contGame = T.countdown();
			playerStats.updateStats(&player);
		}

		//movement
		if (Keyboard::isKeyPressed(Keyboard::Left)) player.rotateLeft();
		else if (Keyboard::isKeyPressed(Keyboard::Right)) player.rotateRight();
		if (Keyboard::isKeyPressed(Keyboard::Up)) player.accelerateForward();
		else if (Keyboard::isKeyPressed(Keyboard::Down)) player.accelerateReverse();

		//shooting
		if (Keyboard::isKeyPressed(Keyboard::Space) && j > 15) {
			j = 0;
			bullets.push_back(new Projectile(player.getX(), player.getY(), player.getRotation()));
		}
		//update objects coordinates
		for (int i = 0; i < bullets.size(); i++) {
			//std::cout << "Update " << i;
			bullets[i]->updatePosition();
			if (!bullets[i]->getActive()) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}
		player.updatePosition();

		asteroidsArray.checkForCollisions(bullets, player);
		asteroidsDestroyed = asteroidsArray.getAsteroidsDestroyed();

		i++; j++;
		window.clear();
		//display game
		if (contGame && player.getActive()) {
			player.incrementScore(asteroidsDestroyed);

			if (asteroidsDestroyed < 45) {
				if (i % (60 - asteroidsDestroyed) == 0) {
					asteroidsArray.spawnAsteroid();
				}
			} else {
				if (i % 15 == 0) {
					asteroidsArray.spawnAsteroid();
				}
			}
			for (int i = 0; i < bullets.size(); i++) {
				if (bullets[i]->getActive() == true) 
					bullets[i]->draw(&window);
			}
			player.draw(&window);
			asteroidsArray.drawAsteroids();
			T.drawTimer(&window);
			playerStats.drawStats(&window);
		}
		//display highscores
		else {
			if (!writtenScore) {
				highscore.insertNode(player.getName(), player.getScore());
				highscore.checkSize();
				writtenScore = true;
			}
			highscore.drawScores(&window,font);
		}

		window.display();
	}
	highscore.writeScores();
	return 0;
}