#include <string> // std::string
#include <vector> // std::vector
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::max. std::min, std::remove

#include "../headers/CribbageFunctions.h"
#include "../headers/DeckFunctions.h"
#include "../headers/Functions.h"
#include "../headers/Windows.h"

Cribbage::Cribbage(int n_players, std::string board_name_input, std::map<std::string, std::vector<int>> window_dims) : deck(n_players, 0) {
	initscr();

	resize_term(
		window_dims["board"].at(0) + window_dims["text_area"].at(0),
		window_dims["board"].at(1) + window_dims["play_area"].at(1)
	);
	refresh();

	number_of_players = n_players;
	board_name = board_name_input;
	
	//header_border_win = CreateNewWinBorder(window_dims["header"]);
	board_border_win = CreateNewWinBorder(window_dims["board"]);
	text_area_border_win = CreateNewWinBorder(window_dims["text_area"]);
	play_area_border_win = CreateNewWinBorder(window_dims["play_area"]);

	//header_win = CreateNewWin(window_dims["header"]);
	board_win = CreateNewWin(window_dims["board"]);
	text_area_win = CreateNewWin(window_dims["text_area"]);
	play_area_win = CreateNewWin(window_dims["play_area"]);

	player0_win = CreateNewWin(window_dims["player0"]);
	player1_win = CreateNewWin(window_dims["player1"]);
	player2_win = CreateNewWin(window_dims["player2"]);

	player_windows = {
		{0, player0_win},
		{1, player1_win},
		{2, player2_win}
	};
}

void Cribbage::StartGame() {
	game_over = false;
	InitializeScores();

	GenerateColourPairs();

	GenerateBoard();
	GenerateWelcomeText();
	GenerateDeck();
	GenerateCardAsciis();
	
	WDisplayEmptyColouredBoard();
	WDisplayPeg(0);
	WDisplayPeg(1);
	WDisplayWelcomeText();
	WDisplayInitialPlayArea();

	refresh_wins();
	wgetch(text_area_win);

	while (!game_over) {
		Round();
		n_round++;
	}
	EndGame();
}

void Cribbage::InitializeScores() {
	scores.clear();
	peg_coords.clear();

	for (int i = 0; i < number_of_players; i++) {
		scores.push_back(0);
		peg_coords.insert(
			{ i, {} }
		);
	}
}

void Cribbage::Round() {
	if (!game_over) {

		WPrintToTextArea("Starting round " + std::to_string(n_round) + "...", true, 0, "center");
		InitializePiles();
		deck.ShuffleDeck();
		Deal();
		DrawStarter();
		WDisplayPlayArea();
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
	if (n_round == 1) {
		deck.DealHands(6);
	}
	else {
		deck.DealHands(deck.GetCurrentPlayerIndex(), 6);
	}
	
	if (deck.GetCurrentPlayerIndex() == user_index) {
		WPrintToTextArea("You are dealing the hands...", true, user_index + 1);
	}
	else {
		WPrintToTextArea("Player " + std::to_string(deck.GetCurrentPlayerIndex()) + " is dealing the hands...", true, deck.GetCurrentPlayerIndex() + 1, "right");
	}
	WDisplayPlayArea();
	WPrintToTextArea("You must send 2 cards to the crib.", true, user_index + 1);

	for (int hand_index = 0; hand_index < deck.GetNumberOfPlayers(); hand_index++) {

		if (hand_index == user_index) {
			PassToCrib(deck.ChooseCardsFromHand(*this, hand_index, 2, "user"));
		}
		else {
			PassToCrib(deck.ChooseCardsFromHand(*this, hand_index, 2, "com"));
		}
	}
}

void Cribbage::DrawStarter() {
	starter = deck.DrawCard();
	WPrintToTextArea("The starter is the " + starter.at(0) + " of " + starter.at(1) + ".", true, 0, "center");

	if (starter.at(0) == "Jack") {
		AddPoints(deck.GetDealerIndex(), 2, "Jack's heels");
	}
}

void Cribbage::ThePlay() {
	WPrintToTextArea("Starting the Play.", true, 0, "center");

	for (int i = 0; i < deck.GetNumberOfPlayers(); i++) {
		active_player_indices_for_play.push_back(i);
	}

	while (active_player_indices_for_play.size() > 0 && !game_over) {
		play_total = 0;
		Cribbage::UpTo31();
		deck.ResetCommonPile("the_play");
	}

	if (!game_over) {
		WPrintToTextArea("The Play is done.", true, 0, "center");
	}

}

void Cribbage::UpTo31() {

	active_player_indices_for_31.clear();

	for (auto player_index : active_player_indices_for_play) {
		active_player_indices_for_31.push_back(player_index);
	}

	while (!game_over && play_total <= 31 && std::find(active_player_indices_for_31.begin(), active_player_indices_for_31.end(), deck.GetCurrentPlayerIndex()) != active_player_indices_for_31.end()) {

		WDisplayPlayArea();

		int min_card_point_value = 11;
		std::vector<std::string> played_card;

		if (deck.GetCurrentPlayerIndex() == user_index) {
			WPrintToTextArea("It is your turn to play.", true, user_index + 1);
		}
		else {
			WPrintToTextArea("It is player " + std::to_string(deck.GetCurrentPlayerIndex()) + "s turn to play.", true, deck.GetCurrentPlayerIndex() + 1, "right");
		}

		std::vector<std::vector<std::string>> current_players_hand = deck.GetHands().at(deck.GetCurrentPlayerIndex());

		for (auto card : current_players_hand) {
			min_card_point_value = std::min(card_value_points[card.at(0)], min_card_point_value);
		}

		if (play_total + min_card_point_value > 31) {
			if (deck.GetCurrentPlayerIndex() == user_index) {
				WPrintToTextArea("You cannot play. The turn passes.", true, user_index + 1);
			}
			else {
				WPrintToTextArea("Player " + std::to_string(deck.GetCurrentPlayerIndex()) + " cannot play. The turn passes.", true, deck.GetCurrentPlayerIndex() + 1, "right");
			}

			RemovePlayerFrom31(deck.GetCurrentPlayerIndex());
		}
		else if (deck.GetHands().at(deck.GetCurrentPlayerIndex()).size() == 0) {
			if (deck.GetCurrentPlayerIndex() == user_index) {
				WPrintToTextArea("You are out of cards and cannot play anymore.", true, user_index + 1);
			}
			else {
				WPrintToTextArea("Player " + std::to_string(deck.GetCurrentPlayerIndex()) + " is out of cards and cannot play anymore.", true, deck.GetCurrentPlayerIndex() + 1, "right");
			}

			RemovePlayerFrom31(deck.GetCurrentPlayerIndex());

			RemovePlayerFromThePlay(deck.GetCurrentPlayerIndex());
		}
		else {
			if (deck.GetCurrentPlayerIndex() == user_index) {
				played_card = deck.ChooseCardsFromHand(*this, deck.GetCurrentPlayerIndex(), 1, "user").at(0);
				while (play_total + card_value_points[played_card.at(0)] > 31) {
					WPrintToTextArea("The play total is too high to play this card. Pick again!", true, user_index + 1, "left", "newline");
					played_card = deck.ChooseCardsFromHand(*this, deck.GetCurrentPlayerIndex(), 1, "user").at(0);
				}
			}
			else {
				played_card = deck.ChooseCardsFromHand(*this, deck.GetCurrentPlayerIndex(), 1, "com").at(0);
				while (play_total + card_value_points[played_card.at(0)] > 31) {
					played_card = deck.ChooseCardsFromHand(*this, deck.GetCurrentPlayerIndex(), 1, "com").at(0);
				}
			}
			deck.ToSidePile(deck.GetCurrentPlayerIndex(), "the_play", played_card);
			deck.ToCommonPile("the_play", played_card);

			if (deck.GetCurrentPlayerIndex() == user_index) {
				WPrintToTextArea("You played the " + played_card.at(0) + " of " + played_card.at(1) + ".", true, user_index + 1);
			}
			else {
				WPrintToTextArea("Player " + std::to_string(deck.GetCurrentPlayerIndex()) + " played the " + played_card.at(0) + " of " + played_card.at(1) + ".", true, deck.GetCurrentPlayerIndex() + 1, "right");
			}

			play_total += card_value_points[played_card.at(0)];

			if (!game_over) {
				ThePlayPoints();
			}
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

	WPrintToTextArea("The Show has started.", true, 0, "center");

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

	WPrintToTextArea("The Show is done.", true, 0, "center");
}

void Cribbage::EndGame() {
	if (deck.GetCurrentPlayerIndex() == user_index) {
		WPrintToTextArea("Congratulations!!! You are the winner!!!", true, user_index + 1);
	}
	else {
		WPrintToTextArea("Player " + std::to_string(deck.GetCurrentPlayerIndex()) + " is the winner, better luck next time!", true, deck.GetCurrentPlayerIndex() + 1, "right");
	}
}