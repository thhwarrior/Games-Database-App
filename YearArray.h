#include <iostream>
#include "LinkedList.h"
#include "Game.h"
using namespace std;

struct YearArrayNode {
	List* salesList;
	List* scoresList;
	bool isEmpty() { return salesList->start == nullptr; }
	void insert(Game* game) {
		salesList->insertSorted(game);
		scoresList->insertSorted(game);
	}
};

struct YearArray {
	YearArrayNode* arr;
	int size = 50;

	YearArray() {
		arr = new YearArrayNode[size];
		for (int i = 0; i < size; i++) {
			arr[i].salesList = new List(1);
			arr[i].scoresList = new List(0);
		}
	}

	YearArrayNode* getLists(int year) { return &arr[year - 1980]; }

	void yearSales(int val, int amount) {
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
			else index = index->next;
		}
		cout << endl;
	}

	void yearScore(int val, int amount) {
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
		YearArrayNode* x = getLists(game->year);
		x->insert(game);
	}

	void printArray() {
		for (int i = 0; i < size; i++) {
			YearArrayNode x = arr[i];
			if (!x.isEmpty()) {
				cout << i + 1980 << ": ";
				arr[i].salesList->printList();
				cout << i + 1980 << ": ";
				arr[i].scoresList->printList();
			}
			else cout << i + 1980 << ": empty" << endl;
		}
	}

	void expand() {
		size *= 2;
		YearArrayNode* newArr = new YearArrayNode[size];
		for (int i = 0; i < size / 2; i++) newArr[i] = arr[i];
		delete arr;
		arr = newArr;
	}
};