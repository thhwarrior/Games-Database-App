#include <iostream>
#include "LinkedList.h"
#include "Game.h"
using namespace std;

struct RatingArrayNode {
	List* salesList;
	List* scoresList;
	bool isEmpty() { return salesList->start == nullptr; }
	void insert(Game* game) {
		salesList->insertSorted(game);
		scoresList->insertSorted(game);
	}
};

struct RatingArray {
	RatingArrayNode* arr;
	int size = 9;

	RatingArray() {
		arr = new RatingArrayNode[size];
		for (int i = 0; i < size; i++) {
			arr[i].salesList = new List(1);
			arr[i].scoresList = new List(0);
		}
	}

	RatingArrayNode* getLists(string rating) { return &arr[convert(rating)]; }

	void ratingSales(string val, int amount) {
		ListNode* index = getLists(val)->salesList->start;
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
			else index= index->next;
		}
		cout << endl;
	}

	void ratingScore(string val, int amount) {
		ListNode* index = getLists(val)->scoresList->start;
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
		RatingArrayNode* x = getLists(game->rating);
		x->insert(game);
	}

	int convert(string rating) {
		if (rating == "E") { return 0; }
		if (rating == "M") { return 1; }
		if (rating == "T") { return 2; }
		if (rating == "E10+") { return 3; }
		if (rating == "K A") { return 4; }
		if (rating == "AO") { return 5; }
		if (rating == "EC") { return 6; }
		if (rating == "RP") { return 7; }
		if (rating == "????") { return 8; }
	}

	void printArray() {
		for (int i = 0; i < size; i++) {
			RatingArrayNode x = arr[i];
			if (!x.isEmpty()) {
				cout << i << ": ";
				arr[i].salesList->printList();
				cout << i << ": ";
				arr[i].scoresList->printList();
			}
			else cout << i << ": empty" << endl;
		}
	}

	void expand() {
		size *= 2;
		RatingArrayNode* newArr = new RatingArrayNode[size];
		for (int i = 0; i < size / 2; i++) newArr[i] = arr[i];
		delete arr;
		arr = newArr;
	}
};