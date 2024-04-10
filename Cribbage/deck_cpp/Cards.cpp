#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "../headers/DeckFunctions.h"

std::vector<std::string> Deck::DrawCard() {
	std::vector<std::string> drawn_card = full_deck.at(0);
	full_deck.erase(full_deck.begin());

	return drawn_card;
}

std::vector<std::vector<std::string>> Deck::ChooseCardsFromHand(int hand_index, int n_cards, std::string player_type) {

	std::vector<std::vector<std::string>> cards_to_be_chosen;
	std::vector<int> card_indices;
	std::vector<int> card_indices_to_choose;
	int card_index_input;

	try {
		if (n_cards > hands.at(hand_index).size()) {
			throw std::runtime_error("Not enough cards in hand.");
		}

		for (int i = 0; i < hands.at(hand_index).size(); i++) {
			card_indices.push_back(i);
		}

		if (player_type == "user") {

			std::cout << std::endl << "Choose " << n_cards << " card(s) (enter the card indices on the left):" << std::endl;

			for (int i = 0; i < n_cards; i++) {

				std::cin >> card_index_input;

				while (
					std::find(
						card_indices.begin(),
						card_indices.end(),
						card_index_input
					) == card_indices.end() &&
					std::find(
						card_indices_to_choose.begin(),
						card_indices_to_choose.end(),
						card_index_input
					) != card_indices_to_choose.end()
					) {
					std::cout << std::endl << "Invalid card choice. Please choose again." << std::endl;
					std::cin >> card_index_input;
				}

				card_indices_to_choose.push_back(card_index_input);
				cards_to_be_chosen.push_back(hands.at(hand_index).at(card_index_input));
			}

			std::sort(card_indices_to_choose.begin(), card_indices_to_choose.end(), std::greater<int>());

			for (auto card_index : card_indices_to_choose) {
				hands.at(hand_index).erase(hands.at(hand_index).begin() + card_index);
			}
		}

		else {
			for (int i = 0; i < n_cards; i++) {

				card_index_input = std::rand() % card_indices.size();

				while (
					std::find(
						card_indices_to_choose.begin(),
						card_indices_to_choose.end(),
						card_index_input
					) != card_indices_to_choose.end()
					) {
					card_index_input = std::rand() % card_indices.size();
				}
				card_indices_to_choose.push_back(card_index_input);
				cards_to_be_chosen.push_back(hands.at(hand_index).at(card_index_input));
			}

			std::sort(card_indices_to_choose.begin(), card_indices_to_choose.end(), std::greater<int>());

			for (auto card_index : card_indices_to_choose) {
				hands.at(hand_index).erase(hands.at(hand_index).begin() + card_index);
			}
		}
	}

	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return cards_to_be_chosen;
}