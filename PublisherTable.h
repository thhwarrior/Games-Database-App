#include <iostream>
#include "LinkedList.h"
#include "Game.h"
using namespace std;

struct PublisherNode {
	List* salesList;
	List* scoresList;
	bool isEmpty() { return salesList->start == nullptr; }
	string getPublisher() { if (!isEmpty()) return salesList->start->game->publisher; else return "null"; }
	void insert(Game* game) {
		salesList->insertSorted(game);
		scoresList->insertSorted(game);
	}
};

struct PublisherTable
{
	PublisherNode* arr;
	int size = 600;

	PublisherTable() {
		arr = new PublisherNode[size];
		for (int i = 0; i < size; i++) {
			arr[i].salesList = new List(1);
			arr[i].scoresList = new List(0);
		}
	}

	void printTable() {
		for (int i = 0; i < size; i++) {
			PublisherNode x = arr[i];
			if (!x.isEmpty()) {
				cout << i << ": ";
				arr[i].salesList->printList();
				cout << i << ": ";
				arr[i].scoresList->printList();
			}
			else cout << i << ": empty" << endl;
		}
	}

	int hash(string publisher) {
		int hash = 0;
		for (int i = 1;i < 4;i++) {
			hash += int(publisher[publisher.size() - i]) * (publisher.size());
		}
		if (publisher == "Daedalic Entertainment") { cout << hash % size; }
		return hash % size;
	}

	PublisherNode* retrieveElement(string publisher) {
		int index = hash(publisher);
		if (arr[index].getPublisher() == publisher) {
			return &arr[index];
		}
		else {
			int i = 0;
			while (arr[(index + i) % size].isEmpty() ||
				arr[(index + i) % size].getPublisher() != publisher) {
				i++;
			}
			return &arr[(index + i) % size];
		}
	}

	void publisherSales(string val, int amount) {
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

	void publisherScore(string val, int amount) {
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
		int index = hash(game->publisher);
		if (arr[index].isEmpty() || arr[index].getPublisher() == game->publisher) {
			arr[index].insert(game);
		}
		else {
			int i = 1;
			while (!arr[(index + i) % size].isEmpty() &&
				arr[(index + i) % size].getPublisher() != game->publisher) {i++;}
			arr[(index + i) % size].insert(game);
		}
	}

	void expand() {
		size *= 2;
		PublisherNode* newArr = new PublisherNode[size];
		for (int i = 0; i < size / 2; i++) newArr[i] = arr[i];
		delete arr;
		arr = newArr;
	}
};