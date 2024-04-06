#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "DeckFunctions.h"

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

void Deck::NextPlayer() {
	current_player_index = (current_player_index + 1) % number_of_players;
}

void Deck::NextPlayer(int player_index) {
	current_player_index = player_index < 0 ? (dealer_index + 1) % number_of_players : (player_index + 1) % number_of_players;
}

void Deck::NextPlayerFromActivePlayers(std::vector<int> active_players) {

	NextPlayer();

	while (std::find(
		active_players.begin(),
		active_players.end(),
		current_player_index
	) == active_players.end()) {

		NextPlayer();
	}
}

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

void Deck::DefineSidePiles(std::vector<std::string> side_pile_names) {
	for (int i = 0; i < number_of_players; i++) {
		std::map<std::string, std::vector<std::vector<std::string>>> empty_side_piles;

		for (auto side_pile_name : side_pile_names) {
			std::vector<std::vector<std::string>> empty_side_pile;

			empty_side_piles.insert({ side_pile_name, empty_side_pile });
		}

		side_piles.push_back(empty_side_piles);
	}
}

void Deck::ToSidePile(int player_idx, std::string pile_name, std::vector<std::vector<std::string>> cards_to_send_to_pile) {

	for (auto card : cards_to_send_to_pile) {
		side_piles.at(player_idx)[pile_name].push_back(card);
	}
}

void Deck::ToSidePile(int player_idx, std::string pile_name, std::vector<std::string> card_to_send_to_pile) {
	side_piles.at(player_idx)[pile_name].push_back(card_to_send_to_pile);
}

void Deck::DefineCommonPiles(std::vector<std::string> side_pile_names) {

	for (std::string side_pile_name : side_pile_names) {
		std::vector<std::vector<std::string>> empty_side_pile;

		common_piles.insert({ side_pile_name, empty_side_pile });
	}
}

void Deck::ToCommonPile(std::string pile_name, std::vector<std::vector<std::string>> cards_to_send_to_pile) {

	for (auto card : cards_to_send_to_pile) {
		common_piles[pile_name].push_back(card);
	}
}

void Deck::ToCommonPile(std::string pile_name, std::vector<std::string> card_to_send_to_pile) {

	common_piles[pile_name].push_back(card_to_send_to_pile);
}

int Deck::GetNumberOfPlayers() {
	return number_of_players;
}

int Deck::GetDealerIndex() {
	return dealer_index;
}

int Deck::GetCurrentPlayerIndex() {
	return current_player_index;
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

std::vector<std::vector<std::string>> Deck::ChooseCardsFromHand(int hand_index, int n_cards, std::string player_type) {

	std::vector<std::vector<std::string>> cards_to_be_chosen;

	if (player_type == "user") {
		int card_index;

		std::vector<int> card_indices(hands.at(hand_index).size());
		for (int i = 0; i < hands.at(hand_index).size(); i++) {
			card_indices[i] = i;;
		}

		std::cout << std::endl << "Choose " << n_cards << " card(s) (enter the card indices on the left):";

		for (int i = 0; i < n_cards; i++) {

			std::cout << std::endl;
			std::cin >> card_index;

			while (std::find(card_indices.begin(), card_indices.end(), card_index) == card_indices.end()) {
				std::cout << std::endl << "Invalid card choice. Please choose again." << std::endl;
				std::cin >> card_index;
			}

			card_indices.erase(
				std::remove(card_indices.begin(),
					card_indices.end(),
					card_index
				),
				card_indices.end()
			);

			cards_to_be_chosen.push_back(hands.at(hand_index).at(card_index));

			hands.at(hand_index).erase(hands.at(hand_index).begin() + card_index);
		}
	}
	else {
		cards_to_be_chosen.push_back(hands.at(hand_index).at(0));
		hands.at(hand_index).erase(hands.at(hand_index).begin());

		cards_to_be_chosen.push_back(hands.at(hand_index).at(0));
		hands.at(hand_index).erase(hands.at(hand_index).begin());
	}
	return cards_to_be_chosen;
}

std::vector<std::string> Deck::DrawCard() {
	std::vector<std::string> drawn_card = full_deck.at(0);
	full_deck.erase(full_deck.begin());

	return drawn_card;
}

std::vector<std::vector<std::vector<std::string>>> Deck::GetHands() {
	return hands;
}

std::vector<std::map<std::string, std::vector<std::vector<std::string>>>> Deck::GetSidePiles() {
	return side_piles;
}

std::map<std::string, std::vector<std::vector<std::string>>> Deck::GetCommonPiles() {
	return common_piles;
}