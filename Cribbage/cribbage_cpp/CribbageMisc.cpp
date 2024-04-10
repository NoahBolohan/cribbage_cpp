#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "CribbageFunctions.h"
#include "DeckFunctions.h"
#include "Functions.h"

void Cribbage::RemovePlayerFromThePlay(int player_index) {
	active_player_indices_for_play.erase(
		std::remove(active_player_indices_for_play.begin(),
			active_player_indices_for_play.end(),
			deck.GetCurrentPlayerIndex()
		),
		active_player_indices_for_play.end()
	);
}

void Cribbage::RemovePlayerFrom31(int player_index) {
	active_player_indices_for_31.erase(
		std::remove(active_player_indices_for_31.begin(),
			active_player_indices_for_31.end(),
			deck.GetCurrentPlayerIndex()
		),
		active_player_indices_for_31.end()
	);
}

void Cribbage::PassToCrib(std::vector<std::vector<std::string>> cards) {
	deck.ToCommonPile("crib", cards.at(0));
	deck.ToCommonPile("crib", cards.at(1));
}

std::vector<std::vector<std::string>> Cribbage::GetCardsFromEnd(std::vector<std::vector<std::string>> cards, int n_cards) {

	std::vector<std::vector<std::string>> cards_to_check = {
						cards.end() - n_cards,
						cards.end() - 1
	};

	return cards_to_check;
}