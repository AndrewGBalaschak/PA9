#include <SFML/Graphics.hpp>
#include "Timer.h"

int main() {
	bool timerStart = false;
	int minute = 0, second = 0, width = 800, height = 600;
	time_t start;
	Timer T;
	sf::RenderWindow window(sf::VideoMode(width, height), "Asteroids");

	sf::Font font;
	font.loadFromFile("Tuffy.ttf");

	sf::Text min("", font);
	min.setString(std::to_string(T.getMin()));
	min.setPosition(width - 80, 7);
	min.setCharacterSize(30);
	sf::Text colon("", font);
	colon.setString(":");
	colon.setPosition(width - 60, 5);
	colon.setCharacterSize(30);
	sf::Text sec("", font);
	sec.setString(std::to_string(T.getSec()));
	sec.setPosition(width - 45, 7);
	sec.setCharacterSize(30);
	sf::Text zero("", font);
	zero.setString("0");
	zero.setPosition(width - 45, 7);
	zero.setCharacterSize(30);

	sf::RectangleShape player(sf::Vector2f(40, 10));
	player.setFillColor(sf::Color::White);
	player.setPosition(130, 385);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			time(&start);
			T.setStart(start);
			timerStart = true;
		}
		if (timerStart) {
			timerStart = T.countdown();
			minute = T.getMin();
			min.setString(std::to_string(minute));
			second = T.getSec();
			sec.setString(std::to_string(second));
		}

		window.clear();
		if (second < 10) {
			window.draw(zero);
			sec.setPosition(width - 28, 7);
		}
		else {
			sec.setPosition(width - 45, 7);
		}
		window.draw(min);
		window.draw(colon);
		window.draw(sec);
		window.display();
	}


	return 0;
}