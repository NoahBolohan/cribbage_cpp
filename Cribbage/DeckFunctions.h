#ifndef DECK_HEADER
#define DECK_HEADER

#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <map> // std::map

class Deck {
	public:
		Deck(int);

		void ResetDeck();
		void ShuffleDeck();
		void NextPlayer();
		void NextPlayer(int);
		void NextPlayerFromActivePlayers(std::vector<int>);
		void DisplayHand(int);
		void DealHands(int, int);
		void DefineSidePiles(std::vector<std::string>);
		void ToSidePile(int, std::string, std::vector<std::vector<std::string>>);
		void ToSidePile(int, std::string, std::vector<std::string>);
		void ClearSidePiles();
		void DefineCommonPiles(std::vector<std::string>);
		void ToCommonPile(std::string, std::vector<std::vector<std::string>>);
		void ToCommonPile(std::string, std::vector<std::string>);
		void ClearCommonPiles();

		int GetNumberOfPlayers();
		int GetDealerIndex();
		int GetCurrentPlayerIndex();

		std::vector<std::string> DrawCard();
		std::vector<std::vector<std::string>> HandToPile(int, std::vector<int>);
		std::vector<std::vector<std::string>> ChooseCardsFromHand(int,int,std::string);

		std::vector<std::vector<std::vector<std::string>>> GetHands();
		std::vector<std::map<std::string, std::vector<std::vector<std::string>>>> GetSidePiles();
		std::map<std::string, std::vector<std::vector<std::string>>> GetCommonPiles();

	private:
		std::vector<std::vector<std::string>> full_deck;

		int number_of_players;
		int current_player_index;
		int dealer_index;

		// `hands` interpretation:
		// vect (all player hands) >> vect (single hand) >> vect (card) >> string (suit and value)
		std::vector<std::vector<std::vector<std::string>>> hands;

		// `side_piles` interpretation:
		// vect (side piles for each player) >> std::map (side piles for a player) >>
		// string : vect (pile name, pile) >> vect (cards) >> vect (card) >> string (suit and value)
		std::vector<std::map<std::string, std::vector<std::vector<std::string>>>> side_piles;

		// `common_piles` interperetation:
		// std::map (pile name, pile) >> vect (cards) >> vect (card) >> string (suit and value)
		std::map<std::string, std::vector<std::vector<std::string>>> common_piles;
		
		std::vector<std::string> card_values = { "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
		std::vector<std::string> card_suits = { "Hearts","Diamonds","Clubs","Spades" };
};

#endif