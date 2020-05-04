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

			if (i % (60 - asteroidsDestroyed) == 0) {
				asteroidsArray.spawnAsteroid();
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
			highscore.checkHighScore(player.getName(), player.getScore());
			highscore.drawScores(&window,font);
			//highscore.writeScores();
		}

		window.display();
	}
	return 0;
}

/*
int main() {
	Score score;
	//score.readScores();

	int minute = 0, second = 0;

	std::string name;

	time_t currentTime;

	//create window
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Azteroidz");
	window.setFramerateLimit(60);

	Texture asteroidTexture;

	asteroidTexture.loadFromFile("asteroidTexture.jpg");

	//set up asteroids
	Asteroid::window = &window;
	Asteroid::texture = &asteroidTexture;
	AsteroidsArray asteroidsArray;
	Asteroid* currentAsteroid = nullptr;

	//event handler
	sf::Event event;

	//objects list
	std::vector<MovingObject*> objs;
	Player player(WIDTH / 2, HEIGHT / 2);
	objs.push_back(&player);

	//timer object
	Timer T;
	//stats object
	Stats stats;

	//timer in upper right corner
	sf::Font font;
	//font.loadFromFile("Tuffy.ttf");

	if (!font.loadFromFile("Tuffy.otf")) {
		//std::cout << "ERROR";
	}

	//std::cout << "Enter name: ";
	std::cin >> name;

	T.setStart();

	//projectile
	sf::RectangleShape bullet(sf::Vector2f(2, 2));
	bullet.setFillColor(sf::Color(255, 255, 255));

	int totalFrames = 0;

	bool gameOver = false;
	int asteroidsDestroyed = 0;

	//game loop
	while (window.isOpen()) {


		while (window.pollEvent(event)) {
			//if the window is closed, close it
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//when the timer still has time left
		if (T.countdown() && gameOver == false) {

			totalFrames++;

			if (totalFrames % 240 == 0)
			{
				currentAsteroid = asteroidsArray.spawnAsteroid();
				objs.push_back(currentAsteroid);
			}

			checkForCollisions(objs);

			asteroidsArray.drawAsteroids();

			gameOver = asteroidsArray.getGameOver();
			asteroidsDestroyed = asteroidsArray.getAsteroidsDestroyed();

			player.incrementScore(asteroidsDestroyed);

			//movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.rotateLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.rotateRight();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.accelerateForward();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.accelerateReverse();

			//shooting
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				objs.push_back(new Projectile(player.getX(), player.getY(), player.getRotation()));
			}
			//update player coordinates
			for (int i = 0; i < objs.size(); i++) {
				////std::cout << "Update " << i;
				objs[i]->updatePosition();
				if (!objs[i]->getActive()) {
					delete objs[i];
					objs.erase(objs.begin() + i);
				}
			}

			stats.updateStats(&player);

			//Render
			window.clear();
			T.drawTimer(&window);
			stats.drawStats(&window);
			for (int i = 0; i < objs.size(); i++)
				objs[i]->draw(&window);
			window.display();
		}
		else { //once timer has run out
			score.checkHighScore(name, player.getScore());
			score.writeScores();

			//render
			window.clear();
			score.drawScores(&window, font);
			window.display();
		}
	}
	return 0;
}
*/
