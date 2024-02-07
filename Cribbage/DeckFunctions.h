#ifndef DECK_HEADER
#define DECK_HEADER

#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector

class Deck {
	public:
		Deck();

		void ResetDeck();
		void ShuffleDeck();

		std::vector<std::string> DrawCard();

		std::vector<std::vector<std::vector<std::string>>> DealHands(int, int);

	private:
		std::vector<std::vector<std::string>> full_deck;
};

#endif