#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "../headers/CribbageFunctions.h"
#include "../headers/DeckFunctions.h"
#include "../headers/Functions.h"

void Cribbage::ThePlayPoints() {
	std::vector<std::vector<std::string>> crib = deck.GetCommonPiles()["crib"];

	// Check fifteen-two
	if (play_total == 15) {
		AddPoints(deck.GetCurrentPlayerIndex(), 2, "Fifteen-two");
	}

	// Check runs
	for (int n_cards = 7; n_cards >= 3; n_cards--) {

		switch (n_cards) {
		case 7:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckRuns(cards_to_check, 7, "Run of seven")) {
					break;
				}
			}
		case 6:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckRuns(cards_to_check, 6, "Run of six")) {
					break;
				}
			}
		case 5:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckRuns(cards_to_check, 5, "Run of five")) {
					break;
				}
			}
		case 4:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckRuns(cards_to_check, 4, "Run of four")) {
					break;
				}
			}
		case 3:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckRuns(cards_to_check, 3, "Run of three")) {
					break;
				}
			}
		default:
			break;
		}
	}

	// Check pairs
	for (int n_cards = 4; n_cards >= 2; n_cards--) {

		switch (n_cards) {
		case 4:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckPairs(cards_to_check, 12, "Four-of-a-kind")) {
					break;
				}
			}
		case 3:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckPairs(cards_to_check, 6, "Nice triple")) {
					break;
				}
			}
		case 2:
			if (deck.GetCommonPiles()["the_play"].size() >= n_cards) {

				std::vector<std::vector<std::string>> cards_to_check = GetCardsFromEnd(
					deck.GetCommonPiles()["the_play"],
					n_cards
				);

				if (CheckPairs(cards_to_check, 2, "That's a pair")) {
					break;
				}
			}
		default:
			break;
		}
	}
}

void Cribbage::GoPoints() {
	AddPoints(
		deck.GetCurrentPlayerIndex(),
		play_total < 31 ? 1 : 2,
		"Go"
	);
}

void Cribbage::TheShowPoints(int player_index, std::vector<std::vector<std::string>> cards_to_count) {

	for (auto& card_indices : ComputeSubsets(0, cards_to_count.size())) {

		std::vector<std::vector<std::string>> subset;

		for (int i : card_indices) {
			subset.push_back(cards_to_count.at(i));
		}

		// Check fifteens
		int value_sum = 0;

		for (auto card : subset) {
			value_sum += card_value_points[card.at(0)];
		}

		if (value_sum == 15) {
			AddPoints(deck.GetCurrentPlayerIndex(), 2, "Fifteen for two");
		}

		// Check nob
		if (subset.size() == 1) {
			if (subset.at(0).at(0) == "Jack" && subset.at(0).at(1) == starter.at(1)) {
				AddPoints(deck.GetCurrentPlayerIndex(), 1, "One for the Jack's nob");
			}
		}
	}

	// Check runs
	CheckRunsForShow(cards_to_count);

	// Check pairs
	CheckPairsForShow(cards_to_count);

	// Check flush
	CheckFlushForShow(cards_to_count);
}


void Cribbage::AddPoints(int player_index, int n_points, std::string announcement) {
	scores.at(player_index) = scores.at(player_index) + n_points;
	AnnouncePoints(n_points, announcement);
}

void Cribbage::AnnouncePoints(int n_points, std::string announcement) {
	std::cout << std::endl;

	if (deck.GetCurrentPlayerIndex() == user_index) {
		std::cout << announcement << "! " << n_points << " points for you!" << std::endl;
	}
	else {
		std::cout << announcement << "! " << n_points << " points for player " << deck.GetCurrentPlayerIndex() << "!" << std::endl;
	}
}

void Cribbage::DisplayScore() {
	std::cout << std::endl;
	for (int i = 0; i < scores.size(); i++) {
		std::cout << "Player " << i << ": " << scores.at(i) << " points" << std::endl;
	}
}