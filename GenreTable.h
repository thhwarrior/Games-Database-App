#include <iostream>
#include "LinkedList.h"
#include "Game.h"
using namespace std;

struct GenreNode {
	List* salesList;
	List* scoresList;
	bool isEmpty() { return salesList->start == nullptr; }
	string getGenre() { if (!isEmpty()) return salesList->start->game->genre; else return "null"; }
	void insert(Game* game) {
		salesList->insertSorted(game);
		scoresList->insertSorted(game);
	}
};

struct GenreTable
{
	GenreNode* arr;
	int size = 40;

	GenreTable() {
		arr = new GenreNode[size];
		for (int i = 0; i < size; i++) {
			arr[i].salesList = new List(1);
			arr[i].scoresList = new List(0);
		}
	}

	void printTable() {
		for (int i = 0; i < size; i++) {
			GenreNode x = arr[i];
			if (!x.isEmpty()) {
				cout << i << ": ";
				arr[i].salesList->printList();
				cout << i << ": ";
				arr[i].scoresList->printList();
			}
			else cout << i << ": empty" << endl;
		}
	}

	int hash(string genre) {
		int hash = 0;
		for (int i = 1;i < 4;i++) {
			hash += int(genre[genre.size() - i]) * (genre.size());
		}
		return hash%size;
	}

	GenreNode* retrieveElement(string genre) {
		int index = hash(genre);
		if (arr[index].getGenre() == genre) {
			return &arr[index];
		}
		else {
			int i = 0;
			while (arr[(index + i) % size].isEmpty() ||
				arr[(index + i) % size].getGenre() != genre) { i++; }
			return &arr[(index + i) % size];
		}
	}

	void genreSales(string val, int amount) {
		ListNode* index = retrieveElement(val)->salesList->start;
		if (index == NULL) {
			cout << "Game not found " << endl;
			return;
		}
		for (int i = 1; i <= amount; i++) {
			cout << i << ". " << index->game->name->name << "  ";
			if (index->next == NULL) {
				cout << "The list of games has been exhausted";
				break;
			}
			else index = index->next;
		}
		cout << endl;
	}

	void genreScore(string val, int amount) {
		ListNode* index = retrieveElement(val)->scoresList->start;
		if (index == NULL) {
			cout << "Game not found " << endl;
			return;
		}
		for (int i = 1; i <= amount; i++) {
			cout << i << ". " << index->game->name->name << "  ";
			if (index->next == NULL) {
				cout << "The list of games has been exhausted";
				break;
			}
			else index = index->next;
		}
		cout << endl;
	}

	void insert(Game* game) {
		int index = hash(game->genre);
		if (arr[index].isEmpty() || arr[index].getGenre() == game->genre) {
			arr[index].insert(game);
		}
		else {
			int i = 1;
			while (!arr[(index + i) % size].isEmpty() &&
					arr[(index + i) % size].getGenre() != game->genre) {i++;}
			arr[(index + i) % size].insert(game);
		}
	}

	void expand() {
		size *= 2;
		GenreNode* newArr = new GenreNode[size];
		for (int i = 0; i < size / 2; i++) newArr[i] = arr[i];
		delete arr;
		arr = newArr;
	}
};