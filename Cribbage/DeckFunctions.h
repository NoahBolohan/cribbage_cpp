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
		int GetDealerIndex();
		int GetCurrentPlayerIndex();

		std::vector<std::string> DrawCard();
		std::vector<std::vector<std::string>> HandToPile(int, std::vector<int>);
		std::vector<std::vector<std::string>> ChooseCardsFromHand(int,int);

		std::vector<std::vector<std::vector<std::string>>> GetHands();

	private:
		std::vector<std::vector<std::string>> full_deck;

		int number_of_players;
		int current_player_index;
		int dealer_index;
		std::vector<std::vector<std::vector<std::string>>> hands;
		const std::vector<std::string> card_values = { "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
		const std::vector<std::string> card_suits = { "Hearts","Diamonds","Clubs","Spades" };
};

#endif