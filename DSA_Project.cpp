#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Developer.h"
#include "Game.h"
#include "GamesGraph.h"
#include "GenreTable.h"
#include "PlatformTable.h"
#include "PublisherTable.h"
#include "RatingArray.h"
#include "SalesTree.h"
#include "YearArray.h"

using namespace std;

bool compare(Game* g1, Game* g2) {
	if (g1 == g2) return false;
	if (g1->genre == g2->genre) {
		if (g1->platform == g2->platform) {
			return true;
		}
	}
	return false;
}

void insertRelatedGames(List* list, GamesGraph* graph) {
	ListNode* outerLoopNode = list->start;
	ListNode* innerLoopNode = list->start;
	while (outerLoopNode != nullptr) {
		while (innerLoopNode != nullptr) {
			if (compare(outerLoopNode->game, innerLoopNode->game)) {
				outerLoopNode->game->name->insert(innerLoopNode->game);
			}
			innerLoopNode = innerLoopNode->next;
		}
		innerLoopNode = list->start;
		outerLoopNode = outerLoopNode->next;
	}
}



int main() {

	int count = 0;
	int amount = -1;
	string val;
	int mode2 = -1;
	int mode = -1;
	DeveloperTable* developerTable = new DeveloperTable();
	GamesGraph* gamesgraph = new GamesGraph();
	GenreTable* genreTable = new GenreTable();
	PlatformTable* platformTable = new PlatformTable();
	PublisherTable* publisherTable = new PublisherTable();
	RatingArray* ratingArray = new RatingArray();
	SalesAVLTree* salesAVLTree = new SalesAVLTree();
	YearArray* yearArray = new YearArray();
	List* userScoreList = new List(0);
	List* salesList = new List(1);
	List* criticScoreList = new List(2);
	List* userCountList = new List(3);

	string name, platform, genre, publisher, developer, rating;
	int year, criticScore, criticCount, userCount;
	float salesNA, salesEU, salesJP, salesOther, salesGlobal, userScore;

	fstream fin;
	fin.open("NewNewDataFile.csv", ios::in);

	vector<string> row;
	string line, word, temp;

	while (getline(fin, line, '\n')) {
		count++;
		//if (count > 300) break;
		cout << count << endl;
		row.clear();

		stringstream str(line);

		//setting up row
		while (getline(str, word, ',')) {
			row.push_back(word);
		}

		
		if (!row[0].empty()) {
			name = row[0];
		}
		else {
			name = "????";
		}

		if (!row[1].empty()) {
			platform = row[1];
		}
		else {
			platform = "???";
		}

		if (row[2] == "0") {
			year = 1990;
		}
		else if (!row[2].empty()) {
			year = stoi(row[2]);
		}
		else {
			year = 1990;
		}

		if (!row[3].empty()) {
			genre = row[3];
		}
		else {
			genre = "????";
		}


		if (!row[4].empty()) {
			publisher = row[4];
		}
		else {
			publisher = "????";
		}

		if (!row[5].empty()) {
			salesNA = stof(row[5]);
		}
		else {
			salesNA = 0;
		}

		if (!row[6].empty()) {
			salesEU = stof(row[6]);
		}
		else {
			salesEU = 0;
		}

		if (!row[7].empty()) {
			salesJP = stof(row[7]);
		}
		else {
			salesJP = 0;
		}

		if (!row[8].empty()) {
			salesOther = stof(row[8]);
		}
		else {
			salesOther = 0;
		}

		if (!row[9].empty()) {
			salesGlobal = stof(row[9]);
		}
		else {
			salesGlobal = 0;
		}

		if (!row[10].empty()) {
			criticScore = stoi(row[10]);
		}
		else {
			criticScore = 0;
		}

		if (!row[11].empty()) {
			criticCount = stoi(row[11]);
		}
		else {
			criticCount = 0;
		}

		if (!row[12].empty()) {
			userScore = stof(row[12]);
		}
		else {
			userScore = 0;
		}

		if (!row[13].empty()) {
			userCount = stoi(row[13]);
		}
		else {
			userCount = 0;
		}

		if (!row[14].empty()) {
			developer = row[14];
		}
		else {
			developer = "????";
		}

		if (!row[15].empty()) {
			rating = row[15];
		}
		else {
			rating = "????";
		}


		Game* game = new Game(platform, year, genre, publisher, 
			                  salesNA, salesEU, salesJP, salesOther,
							  criticScore, criticCount, userScore, userCount, developer, rating);

		salesAVLTree->insert(game, salesGlobal);
		gamesgraph->insert(game, name);
		
		developerTable->insert(game);
		genreTable->insert(game);
		platformTable->insert(game);
		publisherTable->insert(game);
		ratingArray->insert(game);
		yearArray->insert(game);
		userScoreList->insertSorted(game);
		salesList->insertSorted(game);
		criticScoreList->insertSorted(game);
		userCountList->insertSorted(game);

	}
	
	cout << "Inserting Related games into games graph...." << endl;
	insertRelatedGames(salesList, gamesgraph);
	cout << "--- Related games inserted into games graph ---" << endl;

	while (true) {
		cout << endl;
		cout << "Press the associated number to select one of the following option:" << endl << "1. Get the info for a game" << endl << "2. Get games for a certain parameter" << endl;
		cout << "3. Get recommendations for similar Games" << endl << "4. Get a list of the best Games" << endl << "Enter 0 to exit" << endl;
		cin >> mode;
		if (mode == 0)break;
		cout << endl;
		if (mode == 1) {
			while (true) {
				cout << endl;
				cout << "Enter the name of the game or enter y to go back" << endl;
				cin.ignore();
				getline(cin, val);
				if (val == "y")break;
				cout << endl;
				gamesgraph->info(val);
				cout << endl;
				cout << "Press 1 to go back or 2 to find info for another game" << endl;
				cin >> amount;
				if (amount == 1)break;
			}

		}
		else if (mode == 2) {
			while (true) {
				cout << endl;
				cout << "Press the associated number to select one of the following option:" << endl << "1. Get the best Games for a Platform" << endl;
				cout << "2. Get the best games for a year" << endl << "3. Get the best Games for a certain Genre" << endl << "4. Get the best Games for a certain Age Rating" << endl;
				cout << "5. Get the best game from a certain Developer" << endl << "6. Get the best Games for a certain publisher" << endl << "Enter 0 to go back" << endl;
				cin >> mode2;
				if (mode2 == 0)break;
				cout << endl;
				if (mode2 == 1) {
					while (true) {
						cout << endl;
						cout << "Enter the name of the Platform or Enter y to go back" << endl;
						cin.ignore();
						getline(cin, val);
						if (val == "y")break;
						cout << endl;
						cout << "Enter the number of games you want" << endl;
						cin >> amount;
						cout << endl;
						cout << "Enter 1 to get Best games by sales and 2 to get Best Games by User Score" << endl;
						cin >> mode2;
						cout << endl;
						if (mode == 1)platformTable->platformSales(val, amount);
						else if (mode == 2) platformTable->platformScore(val, amount);
						else continue;
					}
				}
				else if (mode2 == 2) {
					int year = -1;
					while (true) {
						cout << endl;
						cout << "Enter the Year or Enter 0 to go back" << endl;
						cin >> year;
						if (year == 0)break;
						cout << endl;
						cout << "Enter the number of games you want" << endl;
						cin >> amount;
						cout << endl;
						cout << "Enter 1 to get Best games by sales and 2 to get Best Games by User Score" << endl;
						cin >> mode;
						cout << endl;
						if (mode == 1)yearArray->yearSales(year, amount);
						else if (mode == 2) yearArray->yearScore(year, amount);
						else continue;
						cout << endl;
					}
				}
				else if (mode2 == 3) {
					while (true) {
						cout << endl;
						cout << "Enter the Genre or Enter y to go back" << endl;
						cin.ignore();
						getline(cin, val);
						if (val == "y")break;
						cout << endl;
						cout << "Enter the number of games you want" << endl;
						cin >> amount;
						cout << endl;
						cout << "Enter 1 to get Best games by sales and 2 to get Best Games by User Score" << endl;
						cin >> mode;
						cout << endl;
						if (mode == 1)genreTable->genreSales(val, amount);
						else if (mode == 2) genreTable->genreScore(val, amount);
						else continue;
					}
				}
				else if (mode2 == 4) {
					while (true) {
						cout << endl;
						cout << "Enter the Age Rating or Enter y to go back" << endl;
						cin.ignore();
						getline(cin, val);
						if (val == "y")break;
						cout << endl;
						cout << "Enter the number of games you want" << endl;
						cin >> amount;
						cout << endl;
						cout << "Enter 1 to get Best games by sales and 2 to get Best Games by User Score" << endl;
						cin >> mode;
						cout << endl;
						if (mode == 1)ratingArray->ratingSales(val, amount);
						else if (mode == 2) ratingArray->ratingScore(val, amount);
						else continue;
					}
				}
				else if (mode2 == 5) {
					while (true) {
						cout << endl;
						cout << "Enter the name of the developer or Enter y to go back" << endl;
						cin.ignore();
						getline(cin, val);
						if (val == "y")break;
						cout << endl;
						cout << "Enter the number of games you want" << endl;
						cin >> amount;
						cout << endl;
						cout << "Enter 1 to get Best games by sales and 2 to get Best Games by User Score" << endl;
						cin >> mode;
						cout << endl;
						if (mode == 1)developerTable->developerSales(val, amount);
						else if (mode == 2) developerTable->developerScore(val, amount);
						else continue;
					}
				}
				else if (mode2 == 6) {
					while (true) {
						cout << endl;
						cout << "Enter the name of the Publisher or Enter y to go back" << endl;
						cin.ignore();
						getline(cin, val);
						if (val == "y")break;
						cout << endl;
						cout << "Enter the number of games you want" << endl;
						cin >> amount;
						cout << endl;
						cout << "Enter 1 to get Best games by sales and 2 to get Best Games by User Score" << endl;
						cin >> mode;
						cout << endl;
						if (mode == 1)publisherTable->publisherSales(val, amount);
						else if (mode == 2) publisherTable->publisherScore(val, amount);
						else continue;
					}
				}
				else continue;
			}
		}
		else if (mode == 3) {
			while (true) {
				cout << endl;
				cout << "Enter the name of the Game or Enter y to go back" << endl;
				cin.ignore();
				getline(cin, val);
				if (val == "y")break;
				cout << endl;
				cout << "Enter the number of games you want" << endl;
				cin >> amount;
				cout << endl;
				cout << "Enter 1 to get Best related games according to sales and 2 to get Best related Games according User Score" << endl;
				cin >> mode;
				cout << endl;
				if (mode == 1)gamesgraph->relatedGamesSales(val, amount);
				else if (mode == 2) gamesgraph->relatedGamesScores(val, amount);
				else continue;
			}
		}
		else if (mode == 4) {
			cout << endl;
			cout << "Press the associated number to select one of the following option:" << endl << "1. Get the Games with the best User Score" << endl;
			cout << "2. Get the Games with the Higest Sales" << endl << "3. Get the games with the Highest Critic Score" << endl << "4. Get the Games with the Highest user Count" << endl;
			cout << "Enter 0 to go back" << endl;
			cin >> mode2;
			if (mode2 == 0)break;
			cout << endl;
			if (mode2 == 1) {
				while (true) {
					cout << endl;
					cout << "Enter the number of games you want or Enter 0 to go back" << endl;
					cin >> amount;
					if (amount == 0)break;
					cout << endl;
					userScoreList->print(amount);
				}
			}
			else if (mode2 == 2) {
				while (true) {
					cout << endl;
					cout << "Enter the number of games you want or Enter 0 to go back" << endl;
					cin >> amount;
					if (amount == 0)break;
					cout << endl;
					salesList->print(amount);
				}
			}
			else if (mode2 == 3) {
				while (true) {
					cout << endl;
					cout << "Enter the number of games you want or Enter 0 to go back" << endl;
					cin >> amount;
					if (amount == 0)break;
					cout << endl;
					criticScoreList->print(amount);
				}
			}
			else if (mode2 == 4) {
				while (true) {
					cout << endl;
					cout << "Enter the number of games you want or Enter 0 to go back" << endl;
					cin >> amount;
					if (amount == 0)break;
					cout << endl;
					userCountList->print(amount);
				}
			}
		}
		else continue;
	}
}




