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
		void NextPlayer();
		void NextPlayer(int);

		std::vector<std::string> DrawCard();

		std::vector<std::vector<std::vector<std::string>>> DealHands(int, int, int);

	private:
		std::vector<std::vector<std::string>> full_deck;

		int number_of_players;
		int current_player_index;
		int dealer_index;
};

#endif