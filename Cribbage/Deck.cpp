#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand

#include "DeckFunctions.h"

Deck::Deck() {
	std::srand(unsigned(std::time(0)));

	ResetDeck();
}

void Deck::ResetDeck() {
	std::vector<std::string> card_values = { "Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
	std::vector<std::string> card_suits = { "Hearts","Diamonds","Clubs","Spades" };

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

std::vector<std::string> Deck::DrawCard() {
	std::vector<std::string> drawn_card = full_deck.at(0);
	full_deck.erase(full_deck.begin());

	return drawn_card;
}

std::vector<std::vector<std::vector<std::string>>> Deck::DealHands(int hand_size, int number_of_players) {

	std::vector<std::vector<std::vector<std::string>>> hands(number_of_players);

	int number_of_cards_left_to_deal = hand_size * number_of_players;
	int player_index = 0;

	while (number_of_cards_left_to_deal > 0) {
		hands.at(player_index).push_back(DrawCard());
		player_index = (player_index + 1) % number_of_players;
		number_of_cards_left_to_deal--;
	}

	return hands;
}