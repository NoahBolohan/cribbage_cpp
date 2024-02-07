#ifndef CRIBBAGE_HEADER
#define CRIBBAGE_HEADER

#include <string>
#include <vector>
#include "DeckFunctions.h"

class Cribbage {
	public:
		Cribbage(int, Deck);

		void Deal();
		void PassToCrib(std::vector<std::vector<std::string>>);
		void DrawStarter();
		void ThePlay();
		void TheShow();

		void Round();

	private:
		int number_of_players;

		Deck deck;
		std::vector<int> scores;
		std::vector<std::vector<std::vector<std::string>>> hands;
		std::vector<std::vector<std::string>> crib;
		std::vector<std::string> starter;

		const int score_target = 121;

		int pegging_total = 0;
		int dealer = 0;

};

#endif