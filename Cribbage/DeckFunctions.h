#include <string>
#include <vector>

class Deck {
	public:
		Deck() {
			ResetDeck();
		}

		void ResetDeck();
		std::string DrawCard();

	private:
		std::vector<std::string> full_deck;
};