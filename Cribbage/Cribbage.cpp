#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max

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
	deck.DealHands(0, 6, number_of_players);

	hands = deck.GetHands();

	for (int hand_index = 0; hand_index < deck.GetNumberOfPlayers(); hand_index++) {

		if (hand_index == 0) {

			std::vector<int> card_indices_for_crib;

			int first_card_index_to_crib;
			int second_card_index_to_crib;

			int card_indices[6] = { 0,1,2,3,4,5 };
			int* cin1_in_indices;
			int* cin2_in_indices;

			std::cout << std::endl << "Your hand is:" << std::endl;

			std::cout << std::endl;
			deck.DisplayHand(hand_index);

			std::cout << std::endl << "Choose two cards to send to the crib (enter the card indices on the left):" << std::endl;

			std::cout << "First card:";
			std::cin >> first_card_index_to_crib;
			cin1_in_indices = std::find(std::begin(card_indices), std::end(card_indices), first_card_index_to_crib);

			std::cout << "Second card:";
			std::cin >> second_card_index_to_crib;
			cin2_in_indices = std::find(std::begin(card_indices), std::end(card_indices), second_card_index_to_crib);

			while (cin1_in_indices == std::end(card_indices) || cin2_in_indices == std::end(card_indices) || first_card_index_to_crib == second_card_index_to_crib) {
				std::cout << std::endl  << "Invalid card choice(s). Please choose again." << std::endl;

				std::cout << "First card:";
				std::cin >> first_card_index_to_crib;
				cin1_in_indices = std::find(std::begin(card_indices), std::end(card_indices), first_card_index_to_crib);

				std::cout << "Second card:";
				std::cin >> second_card_index_to_crib;
				cin2_in_indices = std::find(std::begin(card_indices), std::end(card_indices), second_card_index_to_crib);
			}

			card_indices_for_crib.push_back(first_card_index_to_crib);
			card_indices_for_crib.push_back(second_card_index_to_crib);

			PassToCrib(deck.HandToPile(hand_index, card_indices_for_crib));
		}
		else {
			std::vector<int> card_indices_for_crib{ 0,1 };
			PassToCrib(deck.HandToPile(hand_index, card_indices_for_crib));
		}
	}
}

void Cribbage::PassToCrib(std::vector<std::vector<std::string>> cards) {
	crib.push_back(cards.at(0));
	crib.push_back(cards.at(1));
}

void Cribbage::DrawStarter() {
	starter = deck.DrawCard();

	std::cout << std::endl << "The starter is the " << starter.at(0) << " of " << starter.at(1) << "." << std::endl;
}

void Cribbage::ThePlay() {

	while (pegging_total <= 31) {

	}
}

void Cribbage::Round() {
	deck.ShuffleDeck();
	Deal();
	DrawStarter();
}
