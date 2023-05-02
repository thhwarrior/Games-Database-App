#include "GamesGraph.h"
#include "LinkedList.h"
#include "Game.h"

GamesGraphNode::GamesGraphNode(Game* game, string gameName) {
    this->game = game;
    relatedGamesScores = new List(0);
    relatedGamesSales = new List(1);
    name = gameName;
    height = 1;
    leftChild = nullptr;
    rightChild = nullptr;
}

void GamesGraphNode::insert(Game* game) {
    relatedGamesScores->insertSorted(game);
    relatedGamesSales->insertSorted(game);
}

bool GamesGraph::isEmpty() { return root == nullptr; }

int GamesGraph::height(GamesGraphNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Get the balance factor of each node
int GamesGraph::getBalanceFactor(GamesGraphNode* node) {
    if (node == nullptr) return 0;
    return height(node->leftChild) - height(node->rightChild);
}

void GamesGraph::insert(Game* game, string name) { root = insertValue(root, game, name); }
GamesGraphNode* GamesGraph::insertValue(GamesGraphNode* node, Game* game, string name) {
    if (node == nullptr) {
        GamesGraphNode* newNode = new GamesGraphNode(game, name);
        game->name = newNode;
        return newNode;
    }
    else if (name < node->name) node->leftChild = insertValue(node->leftChild, game, name);
    else if (name > node->name) node->rightChild = insertValue(node->rightChild, game, name);
    else {
        game->name = node;
        node->insert(game);
        return node;
    }

    node->height = 1 + max(height(node->leftChild), height(node->rightChild));
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (name < node->leftChild->name) {
            return rightRotate(node);
        }
        else if (name > node->leftChild->name) {
            node->leftChild = leftRotate(node->leftChild);
            return rightRotate(node);
        }
    }

    if (balanceFactor < -1) {
        if (name > node->rightChild->name) {
            return leftRotate(node);
        }
        else if (name < node->rightChild->name) {
            node->rightChild = rightRotate(node->rightChild);
            return leftRotate(node);
        }
    }
    return node;
}


// Rotate right
GamesGraphNode* GamesGraph::rightRotate(GamesGraphNode* y) {
    GamesGraphNode* x = y->leftChild;
    GamesGraphNode* T2 = x->rightChild;
    x->rightChild = y;
    y->leftChild = T2;
    y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
    x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
    return x;
}

// Rotate left
GamesGraphNode* GamesGraph::leftRotate(GamesGraphNode* x) {
    GamesGraphNode* y = x->rightChild;
    GamesGraphNode* T2 = y->leftChild;
    y->leftChild = x;
    x->rightChild = T2;
    x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
    y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
    return y;
}

GamesGraphNode* GamesGraph::search(string name) {
    GamesGraphNode* pointer = root;
    while (pointer != nullptr && pointer->name != name) {
        if (name > pointer->name) pointer = pointer->rightChild;
        else pointer = pointer->leftChild;
    }
    return pointer;
}

void GamesGraph::printAscending() { inOrderTraversal(root); cout << endl; }
void GamesGraph::inOrderTraversal(GamesGraphNode* current) {
    if (current == nullptr) return;
    inOrderTraversal(current->leftChild);
    cout << current->name << ": ";
    current->relatedGamesScores->printList();
    cout << current->name << ": ";
    current->relatedGamesSales->printList();
    inOrderTraversal(current->rightChild);
}

void GamesGraph::info(string name) {
    GamesGraphNode* val=search(name);
    if (val == NULL) {
        cout << "Game not found " << endl;
        return;
    }
    cout << "Name: " << val->name << endl << "Platform: " << val->game->platform << endl << "Genre: " << val->game->genre << endl << "Year: " << val->game->year << endl << "Developer: " << val->game->developer << endl << "Publisher: " << val->game->publisher << endl << "Critic Score: " << val->game->criticScore << endl << "Critic Count: " << val->game->criticCount << endl << "User Score: " << val->game->userScore << endl << "User Count: " << val->game->userCount << endl << "Global Sales: " << val->game->globalSales->sale << endl << "North America Sales:  " << val->game->salesNA << endl << "Europe Sales: " << val->game->salesEU << endl << "Japan Sales: " << val->game->salesJP << endl << "Other Sales: " << val->game->salesOther << endl;
}

void GamesGraph::relatedGamesSales(string name,int amount) {
    cout << "test";
    ListNode *index=search(name)->relatedGamesSales->start;
  
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

void GamesGraph::relatedGamesScores(string name, int amount) {
    ListNode* index = search(name)->relatedGamesScores->start;
    if (index == NULL || index->next==NULL) {
        cout << "Game not found " << endl;
        return;
    }
    index = index->next;
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