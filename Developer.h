#include <iostream>
#include "LinkedList.h"
#include "Game.h"
using namespace std;

struct DeveloperNode {
	List* salesList;
	List* scoresList;
	bool isEmpty() { return salesList->start == nullptr; }
	string getDeveloper() { if (!isEmpty()) return salesList->start->game->developer; else return "null"; }
	void insert(Game* game) {
		salesList->insertSorted(game);
		scoresList->insertSorted(game);
	}
};

struct DeveloperTable
{
	DeveloperNode* arr;
	int size = 1700;

	DeveloperTable() {
		arr = new DeveloperNode[size];
		for (int i = 0; i < size; i++) {
			arr[i].salesList = new List(1);
			arr[i].scoresList = new List(0);
		}
	}

	void printTable() {
		for (int i = 0; i < size; i++) {
			DeveloperNode x = arr[i];
			if (!x.isEmpty()) {
				cout << i << ": ";
				arr[i].salesList->printList();
				cout << i << ": ";
				arr[i].scoresList->printList();
			}
			else cout << i << ": empty" << endl;
		}
	}

	int hash(string developer) {
		int hash = 0;
		for (int i = 1;i < 4;i++) {
			hash += int(developer[developer.size() - i]) * (developer.size());
		}
		return hash % size;
	}

	DeveloperNode* retrieveElement(string developer) {
		int index = hash(developer);
		if (arr[index].getDeveloper() == developer) {
			return &arr[index];
		}
		else {
			int i = 0;
			while (arr[(index + i) % size].isEmpty() ||
				arr[(index + i) % size].getDeveloper() != developer) {
				i++;
			}
			return &arr[(index + i) % size];
		}
	}

	void developerSales(string val, int amount) {
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

	void developerScore(string val, int amount) {
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
		int index = hash(game->developer);
		if (arr[index].isEmpty() || arr[index].getDeveloper() == game->developer) {
			arr[index].insert(game);
		}
		else {
			int i = 1;
			while (!arr[(index + i) % size].isEmpty() &&
				   arr[(index + i) % size].getDeveloper() != game->developer) {i++;}
			arr[(index + i) % size].insert(game);
		}
	}

	void expand() {
		size *= 2;
		DeveloperNode* newArr = new DeveloperNode[size];
		for (int i = 0; i < size / 2; i++) newArr[i] = arr[i];
		delete arr;
		arr = newArr;
	}
};