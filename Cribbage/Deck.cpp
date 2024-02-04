#include <iostream>
#include <string>
#include <vector>
#include "DeckFunctions.h"

void Deck::ResetDeck() {
	std::vector<std::string> card_values = { "A","1","2","3","4","5","6","7","8","9","10","J","Q","K" };
	std::vector<std::string> card_suits = { "h","d","c","s" };

	full_deck.clear();

	for (std::string v : card_values) {
		for (std::string s : card_suits) {
			full_deck.push_back(v + s);
		}
	}
}

std::string Deck::DrawCard() {
	std::string drawn_card = full_deck.at(0);
	full_deck.erase(full_deck.begin());

	return drawn_card;
}