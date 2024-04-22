#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "../headers/DeckFunctions.h"
#include "../headers/CribbageFunctions.h"

std::vector<std::string> Deck::DrawCard() {
	std::vector<std::string> drawn_card = full_deck.at(0);
	full_deck.erase(full_deck.begin());

	return drawn_card;
}

// TODO: Figure out how to optionally erase card from hand (in situations where chosen card doesn't fit game rules)
std::vector<std::vector<std::string>> Deck::ChooseCardsFromHand(Cribbage &cribbage, int hand_index, int n_cards, std::string player_type) {

	std::vector<std::vector<std::string>> cards_to_be_chosen;
	std::vector<int> card_indices;
	std::vector<int> card_indices_to_choose;
	char temp_input[80];
	int card_index_input;

	try {
		if (n_cards > hands.at(hand_index).size()) {
			throw std::runtime_error("Not enough cards in hand.");
		}

		for (int i = 0; i < hands.at(hand_index).size(); i++) {
			card_indices.push_back(i);
		}

		if (player_type == "user") {

			cribbage.WPrintToTextArea("Choose card(s) (enter the card index beneath):", current_player_index + 1, true, "left", "newline");

			for (int i = 0; i < n_cards; i++) {

				wgetstr(cribbage.GetTextAreaWin(),temp_input);
				card_index_input = atoi(temp_input);
				cribbage.WPrintToTextArea(std::to_string(card_index_input), current_player_index + 1, true, "left", "newline");

				while (std::find(card_indices.begin(), card_indices.end(), card_index_input) == card_indices.end() || std::find(card_indices_to_choose.begin(), card_indices_to_choose.end(), card_index_input) != card_indices_to_choose.end()) {

					cribbage.WPrintToTextArea("Invalid card choice. Please choose again:", current_player_index + 1, true, "left", "newline");

					wgetstr(cribbage.GetTextAreaWin(), temp_input);
					card_index_input = atoi(temp_input);
					cribbage.WPrintToTextArea(std::to_string(card_index_input), current_player_index + 1, true, "left", "newline");
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
		cribbage.WPrintToTextArea(e.what());
	}

	return cards_to_be_chosen;
}