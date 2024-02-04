#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector

class Deck {
	public:
		Deck() {
			std::srand(unsigned(std::time(0)));

			ResetDeck();
		}

		void ResetDeck();
		void ShuffleDeck();

		std::string DrawCard();

		std::vector<std::vector<std::string>> DealHands(int hand_size, int number_of_players);

	private:
		std::vector<std::string> full_deck;
};