#pragma once
#include <iostream>
struct ListNode;
struct List;
struct Game;
using namespace std;

struct SalesAVLNode {
    float sale;
    List* scoresList;
    int height;
    SalesAVLNode* leftChild;
    SalesAVLNode* rightChild;

    SalesAVLNode(float saleValue);

    void insert(Game* game);
};

struct SalesAVLTree
{
    SalesAVLNode* root = nullptr;
    SalesAVLNode* nodeToReturn;

    bool isEmpty();

    int height(SalesAVLNode* node);

    // Get the balance factor of each node
    int getBalanceFactor(SalesAVLNode* node);

    void insert(Game* game, float sale);
    SalesAVLNode* insertValue(SalesAVLNode* node, Game* game, float sale);

    // Rotate right
    SalesAVLNode* rightRotate(SalesAVLNode* y);

    // Rotate left
    SalesAVLNode* leftRotate(SalesAVLNode* x);

    void print();
    void inOrderTraversal(SalesAVLNode* current);
};