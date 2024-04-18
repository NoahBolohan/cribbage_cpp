#include "headers/CribbageFunctions.h"

int main() {
	int number_of_players = 2; //2 for now, 3 eventually

	Cribbage cribbage(
		number_of_players,
		"2p_simple_hori",
		{ 
			{"board", {13, 58, 0, 0}},
			{"text_area", {20, 58, 13, 0}},
			{"play_area", {21, 37, 0, 58}},
			{"player0", {8, 37, 13, 58}},
			{"player1", {7, 37, 0, 58}},
			{"player2", {7, 37, 0, 58}}
		}
	);

	cribbage.StartGame();

	getch();

	return 0;
}