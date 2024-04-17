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

	// Check fifteens
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
	}

	// Check runs
	CheckRunsForShow(cards_to_count);

	// Check pairs
	CheckPairsForShow(cards_to_count);

	// Check flush
	CheckFlushForShow(cards_to_count);

	// Check nob
	for (auto card : cards_to_count) {
		if (card.at(0) == "Jack" && card.at(1) == starter.at(1)) {
			AddPoints(deck.GetCurrentPlayerIndex(), 1, "One for the Jack's nob");
		}
	}
}

void Cribbage::AddPoints(int player_index, int n_points, std::string announcement) {
	scores.at(player_index) = scores.at(player_index) + n_points;
	WDisplayPeg(player_index);
	AnnouncePoints(n_points, announcement);

	if (scores.at(player_index) >= score_target) {
		game_over = true;
	}
}

void Cribbage::AnnouncePoints(int n_points, std::string announcement) {
	std::cout << std::endl;

	if (deck.GetCurrentPlayerIndex() == user_index) {
		WPrintToTextArea({ announcement + "! " + std::to_string(n_points) + " points for you!"}, true);
	}
	else {
		WPrintToTextArea({ announcement + "! " + std::to_string(n_points) + " points for player " +std::to_string(deck.GetCurrentPlayerIndex()) + "!" }, true);
	}
}

void Cribbage::DisplayScore() {
	for (int i = 0; i < scores.size(); i++) {
		std::cout << std::endl << "Player " << i << ": " << scores.at(i) << " points";
	}
}