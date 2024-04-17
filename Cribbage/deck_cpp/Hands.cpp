#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "../headers/DeckFunctions.h"

void Deck::DisplayHand(int hand_index) {
	int setw_size = 0;
	for (auto card : hands.at(hand_index)) {
		int card_size = static_cast<int>(card.at(0).size());
		setw_size = card_size > setw_size ? card_size : setw_size;
	}

	for (int card_index = 0; card_index < hands.at(hand_index).size(); card_index++) {
		std::cout << card_index << ". " << std::setw(setw_size) << std::left << hands.at(hand_index).at(card_index).at(0) << " of " << hands.at(hand_index).at(card_index).at(1) << std::endl;
	}
}

void Deck::DealHands(int d_idx, int hand_size) {

	hands.clear();

	dealer_index = d_idx;
	NextPlayer(d_idx);

	for (int i = 0; i < number_of_players; i++) {
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

void Deck::DealHands(int hand_size) {

	hands.clear();

	NextPlayer(-1);

	for (int i = 0; i < number_of_players; i++) {
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

std::vector<std::vector<std::string>> Deck::HandToPile(int hand_index, std::vector<int> card_indices) {
	std::vector<std::vector<std::string>> cards_to_send;
	std::sort(card_indices.begin(), card_indices.end(), std::greater<>());

	for (int i : card_indices) {
		cards_to_send.push_back(hands.at(hand_index).at(i));
		hands.at(hand_index).erase(hands.at(hand_index).begin() + i);
	}

	return cards_to_send;
}