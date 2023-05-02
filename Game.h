#pragma once
#include <iostream>
#include "GamesGraph.h"
#include "SalesTree.h"
using namespace std;

struct Game {
	GamesGraphNode* name;
	SalesAVLNode* globalSales;
	string platform, genre, publisher, developer, rating;
	int year, criticScore, criticCount, userCount;
	float salesNA, salesEU, salesJP, salesOther, userScore;

	Game(string Platform, int Year, string Genre, string Publisher, float SalesNA,
		float SalesEU, float SalesJP, float SalesOther, int CriticScore,
		int CriticCount, float UserScore, int UserCount, string Developer, string Rating) {

		platform = Platform; year = Year; genre = Genre; publisher = Publisher;
		salesNA = SalesNA; salesEU = SalesEU; salesJP = SalesJP; salesOther = SalesOther;
		criticScore = CriticScore; criticCount = CriticCount;
		userScore = UserScore; userCount = UserCount; developer = Developer; rating = Rating;
	}

	void print() {
		cout << "{ " << name->name << " | " << platform << " | " << year << " | " << genre << " | "
			<< publisher << " | " << salesNA << " | " << salesEU << " | " << salesJP << " | "
			<< salesOther << " | " << globalSales->sale << " | " << criticScore << " | " 
			<< criticCount << " | " << userScore << " | " << userCount << " | " << developer << " | "
			<< rating << " }" << endl;
	}
};