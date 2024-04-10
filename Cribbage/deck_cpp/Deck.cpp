#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "../headers/DeckFunctions.h"

Deck::Deck(int n_players) {
	std::srand(unsigned(std::time(0)));

	number_of_players = n_players;

	ResetDeck();
}

void Deck::ResetDeck() {
	full_deck.clear();

	for (std::string v : card_values) {
		for (std::string s : card_suits) {
			std::vector<std::string> card{ v,s };
			full_deck.push_back(card);
		}
	}
}

void Deck::ShuffleDeck() {
	std::random_shuffle(full_deck.begin(), full_deck.end());
}