#include <iostream> // std::cout, std::cin
#include <string> // std::string
#include <vector> // std::vector
#include <ctime> // std::time 
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "../headers/CribbageFunctions.h"
#include "../headers/DeckFunctions.h"
#include "../headers/Functions.h"
#include "../headers/Windows.h"
#include <pdcurses/curses.h>

Cribbage::Cribbage(int n_players, std::map<std::string, std::vector<int>> window_dims) : deck(n_players) {
	initscr();

	//resize_term(63, 240);
	resize_term(30,120);
	refresh();

	number_of_players = n_players;
	
	header_border_win = create_newwin_border(window_dims["header"]);
	board_border_win = create_newwin_border(window_dims["board"]);
	text_area_border_win = create_newwin_border(window_dims["text_area"]);
	play_area_border_win = create_newwin_border(window_dims["play_area"]);

	header_win = create_newwin(window_dims["header"]);
	board_win = create_newwin(window_dims["board"]);
	text_area_win = create_newwin(window_dims["text_area"]);
	play_area_win = create_newwin(window_dims["play_area"]);
}

void Cribbage::StartGame() {
	game_over = false;
	InitializeScores();

	GenerateColourPairs();

	GenerateBoard();
	GenerateHeader();
	GenerateDeck();
	
	WDisplayBoard("2p_simple_hori");
	WDisplayHeader();
	WDisplayTextArea();
	WDisplayPlayArea();

	refresh_wins();
	getch();

	while (!game_over) {
		Round();
		n_round++;
	}
	EndGame();
}

void Cribbage::InitializeScores() {
	scores.clear();

	for (int i = 0; i < number_of_players; i++) {
		scores.push_back(0);
	}
}

void Cribbage::Round() {
	if (!game_over) {
		std::cout << "Starting round " << n_round << "." << std::endl;
		InitializePiles();
		deck.ShuffleDeck();
		Deal();
		DrawStarter();
		ThePlay();
	}
	if (!game_over) {
		TheShow();
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

void Cribbage::DrawStarter() {
	starter = deck.DrawCard();
	std::cout << std::endl << "The starter is the " << starter.at(0) << " of " << starter.at(1) << "." << std::endl;

	if (starter.at(0) == "Jack") {
		AddPoints(deck.GetDealerIndex(), 2, "Jack's heels");
	}
}

void Cribbage::ThePlay() {

	std::cout << std::endl << "Starting the play. The score is the following:" << std::endl;
	DisplayScore();

	for (int i = 0; i < deck.GetNumberOfPlayers(); i++) {
		active_player_indices_for_play.push_back(i);
	}

	while (active_player_indices_for_play.size() > 0 && !game_over) {
		play_total = 0;
		Cribbage::UpTo31();
		deck.ResetCommonPile("the_play");
	}

	if (!game_over) {
		std::cout << std::endl << "The play is done. The score is the following:" << std::endl;
		DisplayScore();
	}

}

void Cribbage::UpTo31() {

	active_player_indices_for_31.clear();

	for (auto player_index : active_player_indices_for_play) {
		active_player_indices_for_31.push_back(player_index);
	}

	while (!game_over && play_total <= 31 && std::find(active_player_indices_for_31.begin(), active_player_indices_for_31.end(), deck.GetCurrentPlayerIndex()) != active_player_indices_for_31.end()) {

		int min_card_point_value = 11;
		std::vector<std::string> played_card;

		std::cout << std::endl;
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

			if (!game_over) {
				ThePlayPoints();
			}

			std::cout << "The play total is now " << play_total << ".";
		}

		if (active_player_indices_for_play.size() > 0) {
			deck.NextPlayerFromActivePlayers(active_player_indices_for_play);
		}
	}

	if (!game_over) {
		GoPoints();
	}
}

void Cribbage::TheShow() {

	std::cout << "The Show has started." << std::endl;

	deck.NextPlayer(-1);

	for (int i = 0; i < deck.GetNumberOfPlayers(); i++) {

		int player_index = deck.GetCurrentPlayerIndex();

		std::vector<std::vector<std::string>> cards_to_count = deck.GetSidePiles().at(player_index)["the_play"];
		cards_to_count.push_back(starter);

		if (!game_over) {
			TheShowPoints(player_index, cards_to_count);
		}

		if (player_index == deck.GetDealerIndex()) {
			cards_to_count.clear();
			cards_to_count = deck.GetCommonPiles()["crib"];
			cards_to_count.push_back(starter);

			if (!game_over) {
				TheShowPoints(player_index, cards_to_count);
			}
		}

		if (!game_over) {
			deck.NextPlayer();
		}
	}
}

void Cribbage::EndGame() {
	std::cout << std::endl;
	if (deck.GetCurrentPlayerIndex() == user_index) {
		std::cout << "Congratulations!!! You are the winner!!!" << std::endl;
	}
	else {
		std::cout << "Player " << deck.GetCurrentPlayerIndex() << " is the winner, better luck next time!" << std::endl;
	}
	std::cout << "The final score is:" << std::endl;
	DisplayScore();
}