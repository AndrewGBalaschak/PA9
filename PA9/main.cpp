/*
Programmer: Andrew Balaschak, Svetoslav Dimitrov, Seri Nakamura, Garett 
Class: CPTS 122, Spring 2020; Lab Section 14
Programming Assignment:
Date:
Description:
*/

#include <iostream>
#include "header.h"
using namespace std;

int main() {
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Title");

	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}


	return 0;
}