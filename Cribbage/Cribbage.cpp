#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "CribbageFunctions.h"
#include "DeckFunctions.h"
#include "Functions.h"

Cribbage::Cribbage(int n_players) : deck(n_players) {

	number_of_players = n_players;

	InitializeScores();
}

void Cribbage::InitializeScores() {
	scores.clear();

	for (int i = 0; i < number_of_players; i++) {
		scores.push_back(0);
	}
}

void Cribbage::InitializePiles() {
	deck.DefineSidePiles(side_pile_names);
	deck.DefineCommonPiles(side_pile_names);
}


void Cribbage::Deal() {
	deck.DealHands(0, 6);

	for (int hand_index = 0; hand_index < deck.GetNumberOfPlayers(); hand_index++) {

		if (hand_index == user_index) {
			std::cout << std::endl << "Your hand is:" << std::endl;

			std::cout << std::endl;
			deck.DisplayHand(hand_index);

			std::cout << std::endl << "You must send 2 cards to the crib." << std::endl;
			PassToCrib(deck.ChooseCardsFromHand(hand_index, 2, "user"));
		}
		else {
			PassToCrib(deck.ChooseCardsFromHand(hand_index, 2, "com"));
		}
	}
}

void Cribbage::PassToCrib(std::vector<std::vector<std::string>> cards) {
	deck.ToCommonPile("crib", cards.at(0));
	deck.ToCommonPile("crib", cards.at(1));
}

void Cribbage::DrawStarter() {
	starter = deck.DrawCard();
	std::cout << std::endl << "The starter is the " << starter.at(0) << " of " << starter.at(1) << "." << std::endl;

	if (starter.at(0) == "Jack") {
		AddPoints(deck.GetDealerIndex(), 2, "Jack's heels");
	}
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

std::vector<std::vector<std::string>> Cribbage::GetCardsFromEnd(std::vector<std::vector<std::string>> cards, int n_cards) {

	std::vector<std::vector<std::string>> cards_to_check = {
						cards.end() - n_cards,
						cards.end() - 1
	};

	return cards_to_check;
}

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

bool Cribbage::CheckFlush(std::vector<std::vector<std::string>> cards_to_check, int n_points, std::string announcement) {

	std::vector<std::string> suits;
	bool return_value = false;

	for (auto card : cards_to_check) {
		suits.push_back(card.at(1));
	}

	if (std::adjacent_find(
		suits.begin(),
		suits.end(),
		std::not_equal_to<>()
	) == suits.end()) {

		AddPoints(deck.GetCurrentPlayerIndex(), n_points, announcement);
		return_value = true;
	}

	return return_value;
}

bool Cribbage::CheckRuns(std::vector<std::vector<std::string>> cards_to_check, int n_points, std::string announcement) {

	std::vector<std::string> values;
	bool return_value = false;

	for (auto card : cards_to_check) {
		values.push_back(card.at(0));
	}

	std::vector<int> values_indices;
	std::vector<int> range_indices;

	for (auto value : values) {
		values_indices.push_back(run_ordering[value]);
		if (value == "Ace") {
			values_indices.push_back(13);
		}
	}

	std::sort(values_indices.begin(), values_indices.end());

	for (int i = values_indices.at(0); i <= values_indices.back(); i++) {
		range_indices.push_back(i);
	}

	if (values_indices == range_indices) {

		AddPoints(deck.GetCurrentPlayerIndex(), n_points, announcement);
		return_value = true;
	}

	return return_value;
}

bool Cribbage::CheckPairs(std::vector<std::vector<std::string>> cards_to_check, int n_points, std::string announcement) {

	std::vector<std::string> values;
	bool return_value = false;

	for (auto card : cards_to_check) {
		values.push_back(card.at(0));
	}

	if (std::adjacent_find(
		values.begin(),
		values.end(),
		std::not_equal_to<>()
	) == values.end()) {

		AddPoints(deck.GetCurrentPlayerIndex(), n_points, announcement);
		return_value = true;
	}

	return return_value;
}

void Cribbage::GoPoints() {
	AddPoints(
		deck.GetCurrentPlayerIndex(),
		play_total < 31 ? 1 : 2,
		"Go"
	);
}

void Cribbage::ThePlay() {

	std::cout << std::endl << "Starting the play. The score is the following:" << std::endl;
	DisplayScore();

	for (int i = 0; i < deck.GetNumberOfPlayers(); i++) {
		active_player_indices_for_play.push_back(i);
	}

	while (active_player_indices_for_play.size() > 0) {
		play_total = 0;
		Cribbage::UpTo31();
		deck.ResetCommonPile("the_play");
	}

	std::cout << std::endl << "The play is done. The score is the following:" << std::endl;
	DisplayScore();
}

void Cribbage::UpTo31() {

	active_player_indices_for_31.clear();

	for (auto player_index : active_player_indices_for_play) {
		active_player_indices_for_31.push_back(player_index);
	}

	while (play_total <= 31 && std::find(active_player_indices_for_31.begin(), active_player_indices_for_31.end(), deck.GetCurrentPlayerIndex()) != active_player_indices_for_31.end()) {

		int min_card_point_value = 11;
		std::vector<std::string> played_card;

		std::cout << std::endl << "Play total is " << play_total << ". It is ";
		if (deck.GetCurrentPlayerIndex() == user_index) {
			std::cout << "your turn." << std::endl;
		}
		else {
			std::cout << "player " << deck.GetCurrentPlayerIndex() << "s turn." << std::endl;
		}

		std::vector<std::vector<std::string>> current_players_hand = deck.GetHands().at(deck.GetCurrentPlayerIndex());

		for (auto card : current_players_hand) {
			min_card_point_value = std::min(card_value_points[card.at(0)], min_card_point_value);
		}

		if (play_total + min_card_point_value > 31) {
			if (deck.GetCurrentPlayerIndex() == user_index) {
				std::cout << std::endl << "You cannot play. The turn passes." << std::endl;
			}
			else {
				std::cout << std::endl << "Com " << deck.GetCurrentPlayerIndex() << " cannot play. The turn passes." << std::endl;
			}

			RemovePlayerFrom31(deck.GetCurrentPlayerIndex());
		}
		else if (deck.GetHands().at(deck.GetCurrentPlayerIndex()).size() == 0) {
			if (deck.GetCurrentPlayerIndex() == user_index) {
				std::cout << "You are";
			}
			else {
				std::cout << "Player " << deck.GetCurrentPlayerIndex() << " is";
			}

			std::cout << " out of cards and cannot play anymore." << std::endl;

			RemovePlayerFrom31(deck.GetCurrentPlayerIndex());

			RemovePlayerFromThePlay(deck.GetCurrentPlayerIndex());
		}
		else {
			if (deck.GetCurrentPlayerIndex() == user_index) {
				std::cout << std::endl << "Your turn to play." << std::endl;
				deck.DisplayHand(deck.GetCurrentPlayerIndex());
				played_card = deck.ChooseCardsFromHand(deck.GetCurrentPlayerIndex(), 1, "user").at(0);
			}
			else {
				std::cout << std::endl << "Com " << deck.GetCurrentPlayerIndex() << "s turn to play." << std::endl;
				played_card = deck.ChooseCardsFromHand(deck.GetCurrentPlayerIndex(), 1, "com").at(0);
			}
			deck.ToSidePile(deck.GetCurrentPlayerIndex(), "the_play", played_card);
			deck.ToCommonPile("the_play", played_card);

			if (deck.GetCurrentPlayerIndex() == user_index) {
				std::cout << std::endl << "You ";
			}
			else {
				std::cout << std::endl << "Com " << deck.GetCurrentPlayerIndex() << " ";
			}
			std::cout << "played the " << played_card.at(0) << " of " << played_card.at(1) << std::endl;

			play_total += card_value_points[played_card.at(0)];

			ThePlayPoints();

			std::cout << "The play total is now " << play_total << ".";
		}

		if (active_player_indices_for_play.size() > 0) {
			deck.NextPlayerFromActivePlayers(active_player_indices_for_play);
		}
	}

	GoPoints();
}

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

void Cribbage::TheShow() {

	std::cout << "The Show has started." << std::endl;

	deck.NextPlayer(-1);

	for (int i = 0; i < deck.GetNumberOfPlayers(); i++) {

		int player_index = deck.GetCurrentPlayerIndex();

		std::vector<std::vector<std::string>> cards_to_count = deck.GetSidePiles().at(player_index)["the_play"];
		cards_to_count.push_back(starter);

		TheShowPoints(player_index, cards_to_count);

		if (player_index == deck.GetDealerIndex()) {
			cards_to_count.clear();
			cards_to_count = deck.GetCommonPiles()["crib"];
			cards_to_count.push_back(starter);

			TheShowPoints(player_index, cards_to_count);
		}

		deck.NextPlayer();
	}
}

void Cribbage::TheShowPoints(int player_index, std::vector<std::vector<std::string>> cards_to_count) {
	
	for (auto &card_indices : ComputeSubsets(0, cards_to_count.size())) {

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

		// Check runs

		// Check pairs
		if (subset.size() == 2) {
			CheckPairs(subset, 2, "Nice pair");
		}

		// Check flush
		if (subset.size() == 5) {
			CheckPairs(subset, 5, "What a flush");
		}

		// Check nob
		if (subset.size() == 1) {
			if (subset.at(0).at(0) == "Jack" && subset.at(0).at(1) == starter.at(1)) {
				AddPoints(deck.GetCurrentPlayerIndex(), 1, "One for the Jack's nob");
			}
		}
	}
}

void Cribbage::AddPoints(int player_index, int n_points, std::string announcement) {
	scores.at(player_index) = scores.at(player_index) + n_points;
	AnnouncePoints(n_points, announcement);
}

void Cribbage::DisplayScore() {
	std::cout << std::endl;
	for (int i = 0; i < scores.size(); i++) {
		std::cout << "Player " << i << ": " << scores.at(i) << " points" << std::endl;
	}
}

void Cribbage::Round() {
	InitializePiles();
	deck.ShuffleDeck();
	Deal();
	DrawStarter();
	ThePlay();
	TheShow();
}
