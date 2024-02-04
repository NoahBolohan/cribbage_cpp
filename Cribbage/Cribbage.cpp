#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand

#include "CribbageFunctions.h"
#include "DeckFunctions.h"

Cribbage::Cribbage(int n_players, Deck d) {
	number_of_players = n_players;
	deck = d;
	for (int i = 0; i < n_players; i++) {
		scores.push_back(0);
	}
}

void Cribbage::Deal() {
	deck.DealHands(6,number_of_players);
}

void Cribbage::PassToCrib(std::string card1, std::string card2) {
	crib.push_back(card1);
	crib.push_back(card2);
}

void Cribbage::DrawStarter() {
	starter = deck.DrawCard();
}

void Cribbage::ThePlay(int starting_player) {
	while (pegging_total <= 31) {

	}
}