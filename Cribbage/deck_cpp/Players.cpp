#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <algorithm> // std::random_shuffle, std::sort
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <iomanip> // std::setw

#include "../headers/DeckFunctions.h"

void Deck::NextDealer() {
	dealer_index = (dealer_index + 1) % number_of_players;
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