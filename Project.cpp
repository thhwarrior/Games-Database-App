//#include <iostream>
//#include "Game.h"
//#include "LinkedList.h"
//#include "PlatformTable.h"
//#include "YearArray.h"
//#include "GenreTable.h"
//#include "PublisherTable.h"
//#include "Developer.h"
//#include "RatingArray.h"
//#include "GamesGraph.h"
//#include "SalesTree.h"
//using namespace std;
//
//bool compare(Game* g1, Game* g2) {
//	if (g1 == g2) return false;
//	if (g1->genre == g2->genre) {
//		if (g1->platform == g2->platform) {
//			return true;
//		}
//	}
//	return false;
//}
//
//void insertRelatedGames(List* list, GamesGraph* graph) {
//	ListNode* outerLoopNode = list->start;
//	ListNode* innerLoopNode = list->start;
//	while (outerLoopNode != nullptr) {
//		while (innerLoopNode != nullptr) {
//			if (compare(outerLoopNode->game, innerLoopNode->game)) {
//				outerLoopNode->game->name->insert(innerLoopNode->game);
//			}
//			innerLoopNode = innerLoopNode->next;
//		}
//		innerLoopNode = list->start;
//		outerLoopNode = outerLoopNode->next;
//	}
//}
//
////int main()
////{
////	PlatformTable* platformTable = new PlatformTable();
////	YearArray* yearArray = new YearArray();
////	GenreTable* genreTable = new GenreTable();
////	PublisherTable* publisherTable = new PublisherTable();
////	DeveloperTable* developerTable = new DeveloperTable();
////	RatingArray* ratingArray = new RatingArray();
////	List* userScoreList = new List(0);
////	List* salesList = new List(1);
////	List* criticScoreList = new List(2);
////	List* userCountList = new List(3);
////	SalesAVLTree* salesTree = new SalesAVLTree();
////	GamesGraph* gamesGraph = new GamesGraph();
////
////	string name = "GTA";
////	float sales = 40;
////	Game* game = new Game("GameCube", 2003, "Action", "Take-Two",
////						  10, 10, 10, 10, 11, 10, 10, 9, "RockStarGames", "M");
////	gamesGraph->insert(game, name);
////	salesTree->insert(game, sales);
////
////	platformTable->insert(game);
////	yearArray->insert(game);
////	genreTable->insert(game);
////	publisherTable->insert(game);
////	developerTable->insert(game);
////	ratingArray->insert(game);
////	userScoreList->insertSorted(game);
////	criticScoreList->insertSorted(game);
////	userCountList->insertSorted(game);
////	salesList->insertSorted(game);
////
////	name = "Mario 64";
////	sales = 41;
////	game = new Game("PC", 2004, "Platformer", "Nintendo",
////					10, 10, 10, 11, 9, 10, 11, 11, "Nintendo", "E");
////	gamesGraph->insert(game, name);
////	salesTree->insert(game, sales);
////
////	platformTable->insert(game);
////	yearArray->insert(game);
////	genreTable->insert(game);
////	publisherTable->insert(game);
////	developerTable->insert(game);
////	ratingArray->insert(game);
////	userScoreList->insertSorted(game);
////	criticScoreList->insertSorted(game);
////	userCountList->insertSorted(game);
////	salesList->insertSorted(game);
////
////	name = "Sonic Heroes";
////	sales = 39;
////	game = new Game("GameCube", 2004, "Action", "Sega",
////					10, 10, 10, 9, 10, 10, 9, 10, "Sega", "E");
////	gamesGraph->insert(game, name);
////	salesTree->insert(game, sales);
////
////	platformTable->insert(game);
////	yearArray->insert(game);
////	genreTable->insert(game);
////	publisherTable->insert(game);
////	developerTable->insert(game);
////	ratingArray->insert(game);
////	userScoreList->insertSorted(game);
////	criticScoreList->insertSorted(game);
////	userCountList->insertSorted(game);
////	salesList->insertSorted(game);
////
////	insertRelatedGames(salesList,gamesGraph);
////
////	platformTable->printTable();
////	yearArray->printArray();
////	genreTable->printTable();
////	publisherTable->printTable();
////	developerTable->printTable();
////	ratingArray->printArray();
////	userScoreList->printList();
////	criticScoreList->printList();
////	userCountList->printList();
////	salesTree->print();
////	gamesGraph->printAscending();
////}