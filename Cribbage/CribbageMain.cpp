#include "headers/CribbageFunctions.h"

int main() {
	int number_of_players = 2;

	if (number_of_players == 2) {
		Cribbage cribbage(
		number_of_players,
		"2p_simple_hori",
		{ 
			{"board", {13, 58, 0, 0}},
			{"text_area", {34, 51, 0, 58}},
			{"play_area", {21, 58, 13, 0}}
		}
		);
	}
	else if (number_of_players == 3) {
		Cribbage cribbage(
			number_of_players,
			"3p_simple_hori",
			{
				{"board", {15, 61, 0, 0}},
				{"text_area", {41, 51, 0, 61}},
				{"play_area", {26, 61, 15, 0}}
			}
		);
	}

	cribbage.StartGame();

	getch();

	return 0;
}