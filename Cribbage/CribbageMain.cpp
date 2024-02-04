#include <iostream>
#include <cstdlib>
#include "CribbageFunctions.h"
#include "DeckFunctions.h"

int main() {
	Deck deck;
	
	deck.ShuffleDeck();
	std::vector<std::vector<std::string>> hands = deck.DealHands(6, 2);

	for (auto card : hands.at(0)) {
		std::cout << card << std::endl;
	}

	system("pause");

	return 0;
}