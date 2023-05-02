#include "SalesTree.h"
#include "LinkedList.h"
#include "Game.h"

SalesAVLNode::SalesAVLNode(float saleValue) {
    scoresList = new List(0);
    sale = saleValue;
    height = 1;
    leftChild = nullptr;
    rightChild = nullptr;
}

void SalesAVLNode::insert(Game* game) { scoresList->insertSorted(game); }

bool SalesAVLTree::isEmpty() { return root == nullptr; }

int SalesAVLTree::height(SalesAVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Get the balance factor of each node
int SalesAVLTree::getBalanceFactor(SalesAVLNode* node) {
    if (node == nullptr) return 0;
    return height(node->leftChild) - height(node->rightChild);
}

void SalesAVLTree::insert(Game* game, float sale) { root = insertValue(root, game, sale); }
SalesAVLNode* SalesAVLTree::insertValue(SalesAVLNode* node, Game* game, float sale) {
    if (node == nullptr) {
        SalesAVLNode* newNode = new SalesAVLNode(sale);
        game->globalSales = newNode;
        return newNode;
    }
    else if (sale < node->sale) node->leftChild = insertValue(node->leftChild, game, sale);
    else if (sale > node->sale) node->rightChild = insertValue(node->rightChild, game, sale);
    else {
        game->globalSales = node;
        node->insert(game);
        return node;
    }

    node->height = 1 + max(height(node->leftChild), height(node->rightChild));
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (sale < node->leftChild->sale) {
            return rightRotate(node);
        }
        else if (sale > node->leftChild->sale) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }
    }

    if (balanceFactor < -1) {
        if (sale > node->rightChild->sale) {
            return leftRotate(node);
        }
        else if (sale < node->rightChild->sale) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }
    }
    return node;
}


// Rotate right
SalesAVLNode* SalesAVLTree::rightRotate(SalesAVLNode* y) {
    SalesAVLNode* x = y->leftChild;
    SalesAVLNode* T2 = x->rightChild;
    x->rightChild = y;
    y->leftChild = T2;
    y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
    x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
    return x;
}

// Rotate left
SalesAVLNode* SalesAVLTree::leftRotate(SalesAVLNode* x) {
    SalesAVLNode* y = x->rightChild;
    SalesAVLNode* T2 = y->leftChild;
    y->leftChild = x;
    x->rightChild = T2;
    x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
    y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
    return y;
}

void SalesAVLTree::print() { inOrderTraversal(root); cout << endl; }
void SalesAVLTree::inOrderTraversal(SalesAVLNode* current) {
    if (current == nullptr) return;
    inOrderTraversal(current->leftChild);
    cout << current->sale << ": ";
    current->scoresList->printList();
    inOrderTraversal(current->rightChild);
}