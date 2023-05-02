#include <iostream>
#include "LinkedList.h"
#include "Game.h"
using namespace std;

struct PlatformNode {
	List* salesList;
	List* scoresList;
	bool isEmpty() { return salesList->start == nullptr; }
	string getPlatform() { if (!isEmpty()) return salesList->start->game->platform; else return "null"; }
	void insert(Game* game) {
		salesList->insertSorted(game);
		scoresList->insertSorted(game);
	}
};

struct PlatformTable
{
	PlatformNode* arr;
	int size = 40;

	PlatformTable() {
		arr = new PlatformNode[size];
		for (int i = 0; i < size; i++) {
			arr[i].salesList = new List(1);
			arr[i].scoresList = new List(0);
		}
	}

	void printTable() {
		for (int i = 0; i < size; i++) {
			PlatformNode x = arr[i];
			if (!x.isEmpty()) {
				cout << i << ": ";
				arr[i].salesList->printList();
				cout << i << ": ";
				arr[i].scoresList->printList();
			}
			else cout << i << ": empty" << endl;
		}
	}

	int hash(string platform) {
		int hash = 0;
		for (int i = 1;i < 3;i++) {
			hash += int(platform[platform.size() - i]) * (platform.size());
		}
		return hash % size;
	}

	PlatformNode* retrieveElement(string platform) {
		int index = hash(platform);
		if (arr[index].getPlatform() == platform) {
			return &arr[index];
		}
		else {
			int i = 0;
			while (arr[(index + i) % size].isEmpty() ||
				arr[(index + i) % size].getPlatform() != platform) { i++; }
			return &arr[(index + i) % size]; 
		}
	}

	void platformSales(string val,int amount) {
		ListNode *index=retrieveElement(val)->salesList->start;
		if (index == NULL) {
			cout << "Game not found " << endl;
			return;
		}
		for (int i = 1; i <= amount; i++) {
			cout <<i<<". "<< index->game->name->name << "  ";
			if (index->next == NULL) {
				cout << "The list of games has been exhausted";
				break;
			}
			else index = index->next;
		}
		cout << endl;
	}

	void platformScore(string val, int amount) {
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
		int index = hash(game->platform);
		if (arr[index].isEmpty() || arr[index].getPlatform() == game->platform) {
			arr[index].insert(game);
		}
		else {
			int i = 1;
			while (!arr[(index + i) % size].isEmpty() && 
					arr[(index + i) % size].getPlatform() != game->platform) { i++; }
			arr[(index + i) % size].insert(game);
		}
	}

	void expand() {
		size *= 2;
		PlatformNode* newArr = new PlatformNode[size];
		for (int i = 0; i < size / 2; i++) newArr[i] = arr[i];
		delete arr;
		arr = newArr;
	}
};