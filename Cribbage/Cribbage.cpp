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
	deck.DealHands(0, 6,number_of_players);
}

void Cribbage::PassToCrib(std::vector<std::string> card1, std::vector<std::string> card2) {
	crib.push_back(card1);
	crib.push_back(card2);
}

void Cribbage::DrawStarter() {
	starter = deck.DrawCard();
}

void Cribbage::ThePlay() {
	deck.NextPlayer(-1);

	while (pegging_total <= 31) {

	}
}