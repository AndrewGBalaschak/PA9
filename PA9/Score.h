#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Score {
private:
	struct Node {
		string name;
		int score;
		Node* prev;
		Node* next;
	};

	Node* head;
	bool sorted;

public:
	Score() {
		head = nullptr;
		sorted = false;
	}

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

	void writeScores() {
		ofstream outfile;
		outfile.open("Highscores.csv");
		if (!sorted) {
			sort();
		}
		Node* current = head;
		while (current != nullptr) {
			outfile << current->name << ", " << current->score << endl;
			current = current->next;
		}

		outfile.close();
	}

	void insertNode(string name, int score) {
		Node* newNode = new Node;

		newNode->name = name;
		newNode->score = score;

		//if head is empty, this node is now the head
		if (isEmpty()) {
			head = newNode;
			newNode->next = nullptr;
			newNode->prev = nullptr;
		}

		//otherwise, we put it at the end
		else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}

			current->next = newNode;

			newNode->prev = current;
			newNode->next = nullptr;
		}

		sorted = false;
	}

	void sort() {
		Node* current = head;

		//advance current forward one so that we can use current->prev
		current = current->next;

		while (current != NULL) {
			Node* newCurrent = current;
			int count = 1;

			//while the node is higher than the score before it, keep moving it left
			while (newCurrent != NULL && newCurrent->prev != NULL && newCurrent->score > newCurrent->prev->score) {
				swap(newCurrent, newCurrent->prev);
				newCurrent = newCurrent->prev;
				count++;
			}

			//fix the offset caused by the swapping
			for (int i = 0; i < count; i++) {
				current = current->next;
			}
		}
		sorted = true;
	}

	void swap(Node* node1, Node* node2) {
		Node* tempPrev = node1->prev;
		Node* tempNext = node1->next;

		node1->prev = node2->prev;
		node1->next = node2->next;

		node2->prev = tempPrev;
		node2->next = tempNext;
	}

	int isEmpty() {
		int status = 0;
		if (head == NULL)
			status = 1;
		return status;
	}
};
#endif