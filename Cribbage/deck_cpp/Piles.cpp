#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "../headers/DeckFunctions.h"

void Deck::DefineSidePiles(std::vector<std::string> side_pile_names) {

	side_piles.clear();

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

	common_piles.clear();

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

void Deck::ResetCommonPile(std::string pile_name) {
	common_piles[pile_name].clear();
}