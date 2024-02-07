#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "DeckFunctions.h"

Deck::Deck() {
	std::srand(unsigned(std::time(0)));

	ResetDeck();
}

void Deck::ResetDeck() {
	std::vector<std::string> card_values = { "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
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

void Deck::NextPlayer() {
	current_player_index = (current_player_index + 1) % number_of_players;
}

void Deck::NextPlayer(int player_index) {
	current_player_index = player_index < 0 ? (dealer_index + 1) % number_of_players : (player_index + 1) % number_of_players;
}

void Deck::DisplayHand(int hand_index) {
	int setw_size = 0;
	for (auto card : hands.at(hand_index)) {
		setw_size = card.at(0).size() > setw_size ? card.at(0).size() : setw_size;
	}

	for (int card_index = 0; card_index < hands.at(hand_index).size(); card_index++) {
		std::cout << card_index << ". " << std::setw(setw_size) << std::left << hands.at(hand_index).at(card_index).at(0) << " of " << hands.at(hand_index).at(card_index).at(1) << std::endl;
	}
}

void Deck::DealHands(int d_idx, int hand_size, int n_players) {

	number_of_players = n_players;
	dealer_index = d_idx;
	NextPlayer(d_idx);

	for (int i = 0; i < n_players; i++) {
		std::vector<std::vector<std::string>> empty_hand;
		hands.push_back(empty_hand);
	}

	int number_of_cards_left_to_deal = hand_size * number_of_players;

	while (number_of_cards_left_to_deal > 0) {
		hands.at(current_player_index).push_back(DrawCard());
		NextPlayer();
		number_of_cards_left_to_deal--;
	}
}

int Deck::GetNumberOfPlayers() {
	return number_of_players;
}

std::vector<std::vector<std::string>> Deck::HandToPile(int hand_index, std::vector<int> card_indices) {
	std::vector<std::vector<std::string>> cards_to_send;
	std::sort(card_indices.begin(), card_indices.end(), std::greater<>());

	for (int i : card_indices) {
		cards_to_send.push_back(hands.at(hand_index).at(i));
		hands.at(hand_index).erase(hands.at(hand_index).begin() + i);
	}

	return cards_to_send;
}

std::vector<std::string> Deck::DrawCard() {
	std::vector<std::string> drawn_card = full_deck.at(0);
	full_deck.erase(full_deck.begin());

	return drawn_card;
}

std::vector<std::vector<std::vector<std::string>>> Deck::GetHands() {
	return hands;
}