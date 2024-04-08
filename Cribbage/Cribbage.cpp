#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "CribbageFunctions.h"
#include "DeckFunctions.h"

Cribbage::Cribbage(int n_players) : deck(n_players) {

	number_of_players = n_players;

	InitializeScores();

	deck.DefineSidePiles(std::vector<std::string> {"the_play"});
	deck.DefineCommonPiles(std::vector<std::string> {"crib", "the_play"});
}

void Cribbage::InitializeScores() {
	scores.clear();

	for (int i = 0; i < number_of_players; i++) {
		scores.push_back(0);
	}
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
		std::cout << std::endl << "2 points to the dealer for the Jack's heels!" << std::endl;
		AddPoints(deck.GetDealerIndex(), 2);
	}
}

void Cribbage::ThePlayPoints() {

}

void Cribbage::GoPoints() {
	AddPoints(
		deck.GetCurrentPlayerIndex(),
		play_total < 31 ? 1 : 2
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
	}

	std::cout << std::endl << "The play is done. The score is the following:" << std::endl;
	DisplayScore();
}

void Cribbage::UpTo31() {

	int min_card_point_value = 11;

	active_player_indices_for_31.clear();

	for (auto player_index : active_player_indices_for_play) {
		active_player_indices_for_31.push_back(player_index);
	}

	while (play_total <= 31 && std::find(active_player_indices_for_31.begin(), active_player_indices_for_31.end(), deck.GetCurrentPlayerIndex()) != active_player_indices_for_31.end()) {
		std::vector<std::string> played_card;

		std::cout << std::endl << "Play total is " << play_total << ". It is ";
		if (deck.GetCurrentPlayerIndex() == user_index) {
			std::cout << "your turn." << std::endl;
		}
		else {
			std::cout << "player " << deck.GetCurrentPlayerIndex() << "s turn." << std::endl;
		}

		for (auto card : deck.GetHands().at(deck.GetCurrentPlayerIndex())) {
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

			std::cout << "The play total is now " << play_total << ".";

			ThePlayPoints();
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

void Cribbage::AddPoints(int player_index, int n_points) {
	scores.at(player_index) = scores.at(player_index) + n_points;
}

void Cribbage::DisplayScore() {
	std::cout << std::endl;
	for (int i = 0; i < scores.size(); i++) {
		std::cout << "Player " << i << ": " << scores.at(i) << " points" << std::endl;
	}
}

void Cribbage::Round() {
	deck.ShuffleDeck();
	Deal();
	DrawStarter();
	ThePlay();
}
