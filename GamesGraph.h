#pragma once
#include <iostream>
struct ListNode;
struct List;
struct Game;
using namespace std;

struct GamesGraphNode {
    string name;
    Game* game;
    List* relatedGamesSales;
    List* relatedGamesScores;
    int height;
    GamesGraphNode* leftChild;
    GamesGraphNode* rightChild;

    GamesGraphNode(Game* game, string gameName);
    void insert(Game* game);
};

struct GamesGraph
{
    GamesGraphNode* root = nullptr;

    bool isEmpty();

    int height(GamesGraphNode* node);

    int getBalanceFactor(GamesGraphNode* node);

    void insert(Game* game, string name);

    GamesGraphNode* insertValue(GamesGraphNode* node, Game* game , string name);

    GamesGraphNode* rightRotate(GamesGraphNode* y);

    GamesGraphNode* leftRotate(GamesGraphNode* x);

    GamesGraphNode* search(string name);

    void info(string name);

    void relatedGamesSales(string name, int amount);

    void relatedGamesScores(string name, int amount);

    void printAscending();
    void inOrderTraversal(GamesGraphNode* current);
};