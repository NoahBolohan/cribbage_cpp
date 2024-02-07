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
		void DisplayHand(int);
		void DealHands(int, int, int);

		int GetNumberOfPlayers();

		std::vector<std::string> DrawCard();
		std::vector<std::vector<std::string>> HandToPile(int, std::vector<int>);

		std::vector<std::vector<std::vector<std::string>>> GetHands();

	private:
		std::vector<std::vector<std::string>> full_deck;

		int number_of_players;
		int current_player_index;
		int dealer_index;
		std::vector<std::vector<std::vector<std::string>>> hands;
};

#endif