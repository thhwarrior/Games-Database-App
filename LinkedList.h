#pragma once
#include <iostream>
#include "Game.h"
using namespace std;

struct ListNode
{
	Game* game;
	ListNode* previous;
	ListNode* next;

	ListNode(ListNode* previousNode, Game* game, ListNode* nextNode) {
		this->game = game;
		previous = previousNode;
		next = nextNode;
	}
};

struct List
{
	ListNode* start = nullptr;
	ListNode* last = nullptr;

	ListNode* ploc = nullptr;
	ListNode* loc = nullptr;
	int mode;

	List(int mode) { this->mode = mode; }

	void insertAtFront(Game* game) {
		ListNode* newNode = new ListNode(nullptr, game, start);
		if (start == nullptr) {
			start = newNode;
			last = newNode;
		}
		else {
			start->previous = newNode;
			start = newNode;
		}
	}

	void insertAtEnd(Game* game) {
		ListNode* newNode = new ListNode(last, game, nullptr);
		if (start == nullptr) {
			start = newNode;
			last = newNode;
		}
		else {
			last->next = newNode;
			last = newNode;
		}
	}

	bool search(Game* game) {
		if (start != nullptr) {
			ploc = nullptr;
			loc = start;

			if (mode == 0) {
				while (loc != nullptr && game->userScore < loc->game->userScore) {
					ploc = loc;
					loc = loc->next;
				}
			}
			else if (mode == 1) {
				while (loc != nullptr && game->globalSales->sale < loc->game->globalSales->sale) {
					ploc = loc;
					loc = loc->next;
				}
			}
			else if (mode == 2) {
				while (loc != nullptr && game->criticScore < loc->game->criticScore) {
					ploc = loc;
					loc = loc->next;
				}
			}
			else if (mode == 3) {
				while (loc != nullptr && game->userCount < loc->game->userCount) {
					ploc = loc;
					loc = loc->next;
				}
			}

			if (loc == nullptr) return false;
			else if (loc->game == game) return true;
			else return false;
		}
		else { return false; }
	}

	void insertSorted(Game* game) {
		if (!search(game)) {
			if (ploc == nullptr) { insertAtFront(game); }
			else if (loc == nullptr) { insertAtEnd(game); }
			else {
				ListNode* newNode = new ListNode(ploc, game, loc);
				ploc->next = newNode;
				loc->previous = newNode;
			}
		}
	}

	void print(int amount) {
		ListNode* index = start;
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

	void printList() {
		if (start != nullptr) {
			cout << "[";
			loc = start;
			while (loc != nullptr) {
				cout << loc->game->name->name << " - " << loc->game->platform;
				loc = loc->next;
				if (loc != nullptr) { cout << " -> "; }
			}
			cout << "]" << endl;
		}
		else { cout << "List is empty" << endl; }
	}
};

