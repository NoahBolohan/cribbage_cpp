#include <string> // std::string
#include <vector> // std::vector
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "../headers/CribbageFunctions.h"
#include "../headers/DeckFunctions.h"
#include "../headers/Functions.h"

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
	for (auto card : cards) {
		deck.ToCommonPile("crib", card);
	}
}

std::vector<std::vector<std::string>> Cribbage::GetCardsFromEnd(std::vector<std::vector<std::string>> cards, int n_cards) {

	std::vector<std::vector<std::string>> cards_to_check = {
						cards.end() - n_cards,
						cards.end()
	};

	return cards_to_check;
}

WINDOW* Cribbage::GetTextAreaWin() {
	return text_area_win;
}

void Cribbage::SetGameOptions(int n_players, std::map<int, std::string> colour_map) {
	number_of_players = n_players;
	player_colour_map = colour_map;
	board_name = board_name_map[n_players];
	window_dims = window_dim_map[n_players];
	window_dims.insert(
		{
			"terminal",
			{
				window_dims["board"].at(0) + window_dims["play_area"].at(0),
				window_dims["board"].at(1) + window_dims["text_area"].at(1),
				0,
				0
			}
		}
	);
}