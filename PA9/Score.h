#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Score {
private:
	struct Node {
		sf::Text textScore;
		string name;
		int score;
		Node* next;
	};

	Node* head;
	int count;

public:
	Score() {
		head = nullptr;
		count = 0;
	}

	//reads score from file
	void readScores() {
		ifstream infile;
		infile.open("Highscores.csv");
		string name, stringScore;
		int score;

		while (!infile.eof()) {
			getline(infile, name, ',');
			getline(infile, stringScore);
			score = stoi(stringScore);

			insertNode(name, score);
		}

		infile.close();
	}

	//writes scores to file
	void writeScores() {
		ofstream outfile;
		outfile.open("Highscores.csv");
		Node* current = head;
		checkSize();

		//write to file
		while (current != nullptr) {
			outfile << current->name << ", " << current->score << endl;
			current = current->next;
		}

		outfile.close();
	}

	//adds a new node with parameters given
	void insertNode(string name, int score) {
		Node* newNode = new Node;

		newNode->name = name;
		newNode->score = score;

		//if head is empty, this node is now the head
		if (isEmpty()) {
			head = newNode;
			newNode->next = nullptr;
		}

		//otherwise, we put it in the correct orderered spot
		else {
			Node* current = head;
			while (current->next != nullptr && current->next->score > newNode->score) {
				current = current->next;
			}

			newNode->next = current->next;
			current->next = newNode;
		}
		count++;
	}

	//checks for empty head
	int isEmpty() {
		int status = 0;
		if (head == NULL)
			status = 1;
		return status;
	}
	//returns score data at index as string
	string getScore(int index) {
		Node* current = head;
		string output;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		output += current->name;
		output += " ";
		output += to_string(current->score);
		return output;
	}

	//displays scores on win
	void drawScores(sf::RenderWindow* win, sf::Font font) {
		Node* current = head;
		int interval = 25, counter = 0; //for some reason this crashes when counter is initialized at 1
		sf::Text highScores("High Scores:", font);
		highScores.setPosition(width / 2, height / 2 - 25);
		highScores.setCharacterSize(25);
		win->draw(highScores);

		while (current != nullptr) {
			current->textScore.setString(getScore(counter));
			current->textScore.setFont(font);
			current->textScore.setPosition(width / 2, height / 2 + interval * counter);
			current->textScore.setCharacterSize(25);

			current->textScore.setOrigin(current->textScore.getLocalBounds().left / 2, current->textScore.getLocalBounds().top / 2);

			win->draw(current->textScore);
			current = current->next;
			counter++;
		}
	}

	//removes last node if >10 entries
	void checkSize() {
		if (count > 10) {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}

			free(current->next);
			current->next = nullptr;
		}
	}

	//checks to see if high score was made
	void checkHighScore(int newScore) {
		Node* current = head;
		string newName;
		while (current != nullptr) {
			if (newScore > current->score) {
				cout << "Enter name: ";
				cin >> newName;
				insertNode(newName, newScore);
			}
		}
		checkSize();
	}
};
#endif